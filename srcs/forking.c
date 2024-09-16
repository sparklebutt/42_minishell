/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:52 by araveala          #+#    #+#             */
/*   Updated: 2024/09/16 11:51:35 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child(t_data *data, int *fds, int x, int flag)
{	
	char **tmp;
	int fd;
	int i = 0;
	
	fd = 0;
	tmp = NULL;
	// printf("\t\tBEFORE FORK data->filename = %s\n", data->tmp->filename);
	data->child[data->child_i] = fork();
	//g_interactive_mode = 1;
	if (data->child[data->child_i] == -1)
		return (error("fork", "first child failed"));
	if (data->child[data->child_i] == 0)
	{
		//close(3); // this closes valgrinds log.txt 
		g_interactive_mode = data->child[data->child_i]; //eeep
		dup_fds(data, fds, x);
		// dprintf(2, "\tbefore redir helper\n");
		if (data->tokens->action == true && redirect_helper(data->tokens, data->x) != 0)
			exit(exit_code(0,0));
		if (data->tokens->h_action == true)
		{
			fd = open(data->tokens->here_file, O_RDWR);
			if (fd <= 0)
				return (error("redirect", "Failed to open input file C"));
			if (dup2(fd, STDIN_FILENO) == -1)
				return (error("redirect", "Failed to duplicate fd"));
			close(fd);
			while (data->tokens->heredoc[i] != NULL)
			{
				printf("%s\n", data->tokens->heredoc[i]);
				i++;
			}
			free_array(data->tokens->heredoc);
		}
		// --------------------------------------------

		// dprintf(2, "\tbefore checking flag\n");
		if (flag == 1)
		{
			// dprintf(2, "\t\texecute builtins\n");
			exec_builtins(*data, data->tokens->args[data->i]);
			exit(exit_code(0, 0));
		}
		// dprintf(2, "\tbefore setting env array\n");
		tmp = set_env_array(data, 0, 0);
		// dprintf(2, "\tbefore execeve\n");
		//int p = 0;
		//while (data->tmp->ex_arr[p] != NULL)
		//{
		//	dprintf(2, "\t\tB data->tmp->ex_arr[%d] = %s\n", p, data->tmp->ex_arr[p]);
		//	p++;
		//}
		//dprintf(2, "\t\tdata->filename = %s\n", data->tmp->filename);
		reset_signals();
		execve(data->tmp->filename, data->tmp->ex_arr, tmp);		
		free_array(tmp);
		exit(exit_code(0, 0));
	}
	//printf("stepped back into parent\n");
	data->tokens->h_action = false;
	data->tokens->action = false;
	data->child_i++;
	if (data->prev_fd != -1)
		close(data->prev_fd);
	close(fds[1]);
	//g_interactive_mode = 1;	
	//close(3);  // this closes valgrinds log.txt
	return (0);
}

int	set_builtin_info(t_data *data, int fds[2], int x)
{
	int i;

	i = 0;
	i = data->i;
	while (data->tokens->args[i] != NULL && data->tokens->args[i][0] != '|')
	{
		if (is_redirect(data->tokens->args[i]) > 0) // change to 0 if input are needed too
		{
			data->tokens->action = true;
			break ;
		}
		i++;
	}
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
	return (0);
}

int	send_to_child(t_data *data, int fds[2], int x)
{
	//printf("\tstepped in send_to_child\n");
	// dprintf(2, "value of data i:%s\n", data->tokens->args[data->i]);
	//if (data->tokens->args[data->i] == NULL)
	//	return (0);
	if (is_builtins(data->tokens->args[data->i]) == 1)
		set_builtin_info(data, fds, x);
	else if (check_path(data->tmp->env_line, 1, data, data->i) != 0)
	{
		//printf("\tcheck_path was a success\n");
		set_array(data);
		/*int lol = 0;
		while (data->tmp->ex_arr[lol] != NULL)
		{
			printf("\t\tA ex_arr[%d] = %s\n", lol, data->tmp->ex_arr[lol]);
			lol++;
		}*/
		child(data, fds, x, 0);
		//printf("\tafter child\n");
		// free_string(data->tmp->filename); // fixed a still reachable, 14.9
		if (data->i > 0 && data->tokens->args[data->i - 1] != NULL && data->tokens->args[data->i - 1][0] == '>')
			data->i++;
		else if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] == '>')
			data->i += 2;
		else if (data->i == data->tokens->array_count) // || data->i == data->tokens->array_count - 1
			return (0);
		if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] == '|')
			data->i++;
	}
	else
		//printf("\t\tsend to child -1\n");
		return (-1);
	return (0);
}

/*~~ pipes and forks , set_env_array could be moved to every instance of env manipulation instead
then freed at the very end of everything~~*/
static int wait_and_close(t_data *data, int status, int fds[2], int x)
{
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

int	pipe_fork(t_data *data)
{
	int	fds[2];
	int	status;
	int	x;

	data->x = 0;
	x = 0;
	data->prev_fd = -1;
	status = 0;
	while (x <= data->tokens->pipe_count)
	{
		if (data->i > data->tokens->array_count)
			return (error("fork", "we are somehow out of bounds"));
		if (pipe(fds) < 0)
		{
			error("fork", "error in pipe perror needed");
			exit(EXIT_FAILURE);
		}
		if (send_to_child(data, fds, x) == -1)
		{
			close(fds[1]);
			close(fds[0]);
			return (-1);
		// if (data->tokens->here_file)
		// {
		// 	// remove file
		// 	free_string(data->tokens->here_file);
		// 	return (-1);
		// }
		}
    //printf("after send to child\n");
		if (data->prev_fd != -1)
			close(data->prev_fd);
		data->prev_fd = fds[0];
		close(fds[1]);
		x++;
	}
	//printf("waiting and closing\n");
	wait_and_close(data, status, fds, x);
	//printf("closed everything\n");
	return (0);
}
