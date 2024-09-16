/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:52 by araveala          #+#    #+#             */
/*   Updated: 2024/09/16 13:34:17 by vkettune         ###   ########.fr       */
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
	data->child[data->child_i] = fork();
	if (data->child[data->child_i] == -1)
		return (error("fork", "first child failed"));
	if (data->child[data->child_i] == 0)
	{
		g_interactive_mode = data->child[data->child_i];
		dup_fds(data, fds, x);
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
		if (flag == 1)
		{
			exec_builtins(*data, data->tokens->args[data->i]);
			exit(exit_code(0, 0));
		}
		tmp = set_env_array(data, 0, 0);
		reset_signals();
		execve(data->tmp->filename, data->tmp->ex_arr, tmp);		
		free_array(tmp);
		free_array(data->tokens->args);
		free_nodes(data->env);
		free(data->tmp->ex_arr);
		close(fds[1]);
		close(fds[0]);
		exit(exit_code(0, 0));
	}
	data->tokens->h_action = false;
	data->tokens->action = false;
	data->child_i++;
	if (data->prev_fd != -1)
		close(data->prev_fd);
	close(fds[1]);
	free_string(data->tmp->filename);
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
		if (is_redirect(data->tokens->args[i]) > 0)
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
	if (data->tokens->args[data->i] == NULL) // might cause an issue later DO NOT DELETE THIS
		return (0);
	// printf("DOES IT GO HERE?\n");
	if (is_builtins(data->tokens->args[data->i]) == 1)
		set_builtin_info(data, fds, x);
	else if (check_path(data->tmp->env_line, 1, data, data->i) != 0)
	{
		// printf("filename maybe? %s\n", data->tmp->filename);
		set_array(data);
		child(data, fds, x, 0);
		if (data->i > 0 && data->tokens->args[data->i - 1] != NULL && data->tokens->args[data->i - 1][0] == '>')
			data->i++;
		else if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] == '>')
			data->i += 2;
		else if (data->i == data->tokens->array_count)
			return (0);
		if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] == '|')
			data->i++;
	}
	else
	{
		// printf("FUCKING HELL\n");
		return (-1);
	}
		
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
		if (data->prev_fd != -1)
			close(data->prev_fd);
		data->prev_fd = fds[0];
		close(fds[1]);
		x++;
	}
	wait_and_close(data, status, fds, x);
	return (0);
}
