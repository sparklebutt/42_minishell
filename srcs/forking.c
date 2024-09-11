/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:52 by araveala          #+#    #+#             */
/*   Updated: 2024/09/11 18:14:39 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child(t_data *data, int *fds, int x, int flag)
{	
	char **tmp;
	//int p = 0;
	tmp = NULL;
	/*printf("aaaaa=%s", data->tokens->output_files[data->x]);
	if (data->tokens->action == false)
			printf("\t\tits feckiung false\n");
		else 
			printf("\t\tits fecking true\n");*/

	data->child[data->child_i] = fork();
	if (data->child[data->child_i] == -1)
		return (error("fork", "first child failed"));
	if (data->child[data->child_i] == 0)
	{
		dup_fds(data, fds, x);
		if (data->tokens->action == true && redirect_helper(data->tokens, data->x) != 0)
		{
			exit(exit_code(0,0));
		}
		//dprintf(2, "heloooo\n");		
		if (flag == 1)
		{
			exec_builtins(*data, data->tokens->args[data->i]);
			exit(exit_code(0, 0));
		}
		
		tmp = set_env_array(data, 0, 0);
		
		//dprintf(2, "exceve tiiiiime\n");
		/*while(data->tmp->ex_arr[p])
		{
			dprintf(2, "data exx ar = %s\n", data->tmp->ex_arr[p]);
			p++;
		}*/
		execve(data->tmp->filename, data->tmp->ex_arr, tmp);
		//execve(data->tmp->ex_arr[0], data->tmp->ex_arr, tmp);
		//free(data->tmp->ex_arr);
		free_array(tmp); // MALLOCED VARIABLE
		exit(exit_code(0, 0));
	}
	data->tokens->action = false;
	data->child_i++;
	if (data->prev_fd != -1)
		close(data->prev_fd);
	close(fds[1]);
	return (0);
}

int	send_to_child(t_data *data, int fds[2], int x)
{
	//int p = 0;
	if (is_builtins(data->tokens->args[data->i]) == 1)
	{
		data->builtin_marker = true;
		child(data, fds, x, 1);
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
		//printf("what the actualy fcuk = %s\n", data->tokens->output_files[data->i]);
		/*while (data->tmp->ex_arr[p])
		{
			printf("~~~\tex arr loc = %d, = %s\n", p, data->tmp->ex_arr[p]);
			p++;
		}*/
		
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
			if (data->tokens->args[data->i] == NULL)
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
		printf("\t\tsend to child -1\n");
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

	data->x = 0; // oth location of outfiles array
	x = 0;
	data->prev_fd = -1;
	//set_env_array(data); // lets remove this aready
	while (x <= data->tokens->pipe_count)
	{
		if (data->i > data->tokens->array_count)
			return (error("fork", "we are somehow out of bounds"));
		if (pipe(fds) < 0){
			error("fork", "error in pipe perror needed");
			exit(EXIT_FAILURE);
		}
		
		//data->x = x;
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
	if (data->tmp->ex_arr != NULL)
	{
		free(data->tmp->ex_arr);
		data->tmp->ex_arr = NULL;
	}
	status = (status >> 8) & 0xFF;
	exit_code(1, status);	
	return (0);
}
