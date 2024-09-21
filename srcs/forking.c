/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:52 by araveala          #+#    #+#             */
/*   Updated: 2024/09/21 08:58:31 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_infile(t_tokens *tokens)
{
	int fd;
	
	printf("check file = %s\n", tokens->input_file);
	fd = open(tokens->input_file, O_RDONLY); 
	if (fd < 0)
		return (error("infile", "Failed to open input file B"));
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (error("infile", "Failed to duplicate fd"));
	}
	// free input file here maybe
	close(fd);
	return (0);
}
// delete temp file at the end of minishell loop
// (or earlier e.g. end of forks, find place)
int	child(t_data *data, int *fds, int x, int flag)
{
	char	**tmp;

	tmp = NULL;
	data->child[data->child_i] = fork();
	if (data->child[data->child_i] == -1)
		return (error("fork", "first child failed"));
	if (data->child[data->child_i] == 0)
	{
		g_interactive_mode = data->child[data->child_i];
		dup_fds(data, fds, x);
		if (data->tokens->action == true
				&& redirect_helper(data->tokens, data->x) != 0)
			free_n_exit(data, fds, 1);
		if (data->tokens->h_action == true)// && data->tokens->in_action == false)
			open_and_fill_heredoc(data->tokens);
		if (data->in_action)
			open_infile(data->tokens);
		if (flag == 1)
		{
			exec_builtins(*data, data->tokens->args[data->i], &data->env);
			free_n_exit(data, fds, 1);
		}
		tmp = set_env_array(data, 0, 0);
		reset_signals(0);
		if (data->tmp->filename != NULL)
			execve(data->tmp->filename, data->tmp->ex_arr, tmp);
		free_array(tmp);
		free_n_exit(data, fds, 1);
	}
	data->tokens->h_action = false;
	data->tokens->action = false;
	data->in_action = false;
	data->child_i++;
	if (data->prev_fd != -1)
		close(data->prev_fd);
	close(fds[1]);
	data->tmp->filename = free_string(data->tmp->filename);
	return (0);//exit_code(1, 0));
}

int	set_builtin_info(t_data *data, int fds[2], int x)
{
	int	i;

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

int	send_to_child_help(t_data *data, int fds[2], int x)
{
	char	**args;

	args = data->tokens->args;
	set_array(data);
	child(data, fds, x, 0);
	if (data->i == data->tokens->array_count)
		return (1);
	if (args[data->i] != NULL && args[data->i][0] == '|')
		data->i++;
	return (0);
}
void	set_bools(t_data *data, char *args)
{
	if (is_redirect(args) == 3)
		data->tokens->action = true;
	else if (is_redirect(args) == 2)
		data->tokens->h_action = true;
	else if (is_redirect(args) == 1)
		data->in_action = true;	
}

int	send_to_child(t_data *data, int fds[2], int x)
{
	char	**args;

	args = data->tokens->args;
	if (args[data->i] == NULL)
		return (0);
	if (args[data->i] != NULL && is_redirect(args[data->i]) > 0)
	{
		while(args[data->i] != NULL && args[data->i][0] != '|' && is_redirect(args[data->i]) > 0)
		{
			set_bools(data, args[data->i]);
			data->i += 2;
		}
		if (args[data->i] != NULL && args[data->i][0] == '|')
			data->i++;
		if (args[data->i] != NULL && check_path(data->tmp->env_line, 1, data, data->i) == 0)
			return (-1);
		if (send_to_child_help(data, fds, x) == 1)
			return (0);
		data->i++;
	}
	else if (is_builtins(args[data->i]) == 1)
		set_builtin_info(data, fds, x);
	else if (args[data->i] != NULL && check_path(data->tmp->env_line, 1, data, data->i) != 0)
	{
		if (send_to_child_help(data, fds, x) == 1)
			return (0);
	}	
	else if (args[data->i] != NULL)
		return (-1);
	return (0);
}

/*~~ pipes and forks , set_env_array could be moved to every instance 
of env manipulation instead then freed at the very end of everything~~*/
static int	wait_and_close(t_data *data, int status, int fds[2], int x)
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
	if (data->tokens->here_file != NULL)
	{
		dprintf(2, "B UNLINK\n");
	 	unlink(data->tokens->here_file);
	 	data->tokens->here_file = free_string(data->tokens->here_file);
		free_array(data->tokens->heredoc);
		data->tokens->heredoc = NULL;
	}
	status = (status >> 8) & 0xFF;
	exit_code(1, status);
	return (0);
}

int	pipe_fork(t_data *data, int x, int status)
{
	int	fds[2];

	data->x = 0;
	data->prev_fd = -1;
	while (x <= data->tokens->pipe_count)
	{
		if (data->i > data->tokens->array_count)
			return (error("fork", "we are somehow out of bounds"));
		if (pipe(fds) < 0)
		{
			error("pipe", "error running pipe()");
			free_n_exit(data, 0, 0);
		}
		if (send_to_child(data, fds, x) == -1)
		{
			if (data->prev_fd != -1)
				close(data->prev_fd);
			close(fds[1]);
			close(fds[0]);
			return (-1);
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
