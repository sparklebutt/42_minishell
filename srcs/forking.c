/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:52 by araveala          #+#    #+#             */
/*   Updated: 2024/09/21 21:16:01 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_tokens *tokens)
{
	int	fd;

	fd = 0;
	if (tokens->input_file == NULL)
	{
		fd = open("/dev/null", O_RDONLY);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (error("infile", "Failed to duplicate fd"));
		}
		close(fd);
		return (0);
	}
	fd = open(tokens->input_file, O_RDONLY);
	if (fd < 0)
		return (error("infile", "Failed to open input file B"));
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (error("infile", "Failed to duplicate fd"));
	}
	close(fd);
	return (0);
}

int	child(t_data *data, int *fds, int x, int flag)
{
	char	**tmp;

	tmp = NULL;
	data->child[data->child_i] = fork();
	if (data->child[data->child_i] == -1)
		return (error("fork", "first child failed"));
	if (data->child[data->child_i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		dup_fds(data, fds, x);
		if (data->tokens->action == true
			&& redirect_helper(data->tokens, data->x) != 0)
			free_n_exit(data, fds, 1);
		if (data->h_action == true)
			open_and_fill_heredoc(data->tokens);
		if (data->in_action)
			open_infile(data->tokens);
		if (flag == 1)
			exec_builtins(*data, data->tokens->args[data->i], &data->env);
		if (flag == 1)
			free_n_exit(data, fds, 1);
		execve_fail(data, tmp, fds);
	}
	after_child(data, fds);
	return (0);
}

int	send_to_child(t_data *data, int fds[2], int x)
{
	char	**args;

	args = data->tokens->args;
	if (args[data->i] == NULL)
		return (0);
	if (args[data->i] != NULL && is_redirect(args[data->i]) > 0)
	{
		if (checks_before_redir(data, args) == -1)
			return (-1);
		if (send_to_child_help(data, fds, x) == 1)
			return (0);
	}
	else if (is_builtins(args[data->i]) == 1)
		set_builtin_info(data, fds, x);
	else if (args[data->i] != NULL
		&& check_path(data->tmp->env_line, 1, data, data->i) != 0)
	{
		if (send_to_child_help(data, fds, x) == 1)
			return (0);
	}	
	else if (args[data->i] != NULL)
		return (-1);
	return (0);
}

static int	wait_and_close(t_data *data, int status, int fds[2], int x)
{
	close_diff_fds(fds, data, 0);
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
			close_diff_fds(fds, data, 0);
			return (-1);
		}
		close_diff_fds(fds, data, 2);
		x++;
	}
	wait_and_close(data, status, fds, x);
	return (0);
}
