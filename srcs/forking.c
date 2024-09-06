/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:52 by araveala          #+#    #+#             */
/*   Updated: 2024/09/06 16:23:27 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// signal handeling, each child gets the same signal and paret should ignore
int	child(t_data *data, int *fds, int x, int flag)
{	
  	if (flag == 100) 
	  printf("A");
	data->child[data->child_i] = fork();
	if (data->child[data->child_i] == -1)
		return (error("fork", "first child failed"));
	if (data->child[data->child_i] == 0)
	{
		dup_fds(data, fds, x);
		if (redirect_helper(data->tokens, x) != 0)
			exit(exit_code(0,0));
		if (flag == 1)
		{
			exec_builtins(*data, data->tokens->args[data->i]);
			// dprintf(2, "did the exit code atleast change in here = %d\n", exit_code(0,0));
			exit(exit_code(0, 0));
		}
		// printf("execution time check = %s\n", data->tmp->filename);
		execve(data->tmp->filename, data->tmp->ex_arr, data->env_array);
		exit(exit_code(0, 0));
	}
	data->child_i++;
	if (data->prev_fd != -1)
		close(data->prev_fd);
	close(fds[1]);
	return (0);
}

int	send_to_child(t_data *data, int fds[2], int x)
{
	if (is_builtins(data->tokens->args[data->i]) == 1)
	{
		data->builtin_marker = true;
		child(data, fds, x, 1);
		//dprintf(2, "after child\n");
		data->i++;
		while (data->tokens->args[data->i] != NULL)
		{
			if (data->tokens->args[data->i][0] == '|')
			{
				data->i++;
				break ;
			}
			data->i++;
		}
	}
	else if (check_path(data->tmp->env_line, 1, data, data->i) != 0)
	{
		set_array(data);
		if (data->i > 0 && data->builtin_marker == false && data->tokens->args[data->i - 1] != NULL && data->tokens->args[data->i - 1][0] == '>')
		{	
			child(data, fds, x, 2);
			data->i++;
		}
		else if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] == '>')
		{
			child(data, fds, x, 2);
			data->i += 2;
		}
		else if (data->i == data->tokens->array_count - 1)
		{
			
			/*~~ this check is to see if we are on our last on the list of tokens~~*/
			if (data->tokens->args[data->i] == NULL) // was causing sg cd
				child(data, fds, x, 3);
			if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] == '|')
				data->i++;
			return (0);
		}
		else if (data->i == data->tokens->array_count)
		{
			child(data, fds, x, 0);
			return (0);
		}
		else
			child(data, fds, x, 0);
		if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] == '|')
			data->i++;
	}
	else
	{
		printf("send to child -1\n");
		return (-1);
	}
	return (0);
}
/*~~ pipes and forks , set_env_array could be moved to every instance of env manipulation instead
then freed at the very end of everything~~*/
int	pipe_fork(t_data *data)
{
	int	fds[2];
	int	status;
	int	x;

	x = 0;
	data->prev_fd = -1;
	set_env_array(data);
	while (x <= data->tokens->pipe_count)
	{
		if (data->i > data->tokens->array_count)
			return (error("fork", "we are somehow out of bounds"));
		if (pipe(fds) < 0){
			error("fork", "error in pipe perror needed");
			exit(EXIT_FAILURE);
		} // eg example Env | grep PATH=
		data->x = x; // this can be singled down to data->x for example
		if (send_to_child(data, fds, x) == -1)
			return (-1);
		data->prev_fd = fds[0];
		x++;
	}
	close(fds[0]);
	close(fds[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	while (data->child_i >= 0)
	{
		waitpid(data->child[data->child_i], &status, 0);
		x--;
		data->child_i--;
	}
	status = (status >> 8) & 0xFF;
	exit_code(1, status);	
	//alternative 
//	if (status == 256)
//		status = 1;
	/*~~this is how to handle forced overflow for the xit code , as exit code gives bytes not an integer~~*/
	printf("lets look at status for exit codes, pipe_fork= %d\n", status);
	free_array(data->env_array);
	return (0);
}

/*~~ this is not handleing if bultins at all ~~*/
int	simple_fork(t_data *data)
{
	int	status;

	status = 0;
	data->pid = fork();
	if (data->pid == -1)
	{
		ft_printf("fork error\n"); // change error message
		exit(1);
	}
	if (data->pid == 0)
	{	
		if (data->tokens->redirect_count >= 1) // define tems better?
			redirect_helper(data->tokens, 0);
		if (execve(data->tmp->filename, data->tmp->ex_arr, data->env_array) == -1)
			ft_printf("exceve fail\n");
		exit(1); // should this be different kind of error handelin
	}
	waitpid(data->pid, &status, 0);
	return (0);
}