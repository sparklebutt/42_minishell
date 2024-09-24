/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 04:44:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/24 18:39:40 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_and_fill_heredoc(t_tokens *tokens)
{
	int	fd;

	fd = 0;
	if (tokens->ignore_heredoc == true)
	{
		fd = open("/dev/null", O_RDONLY);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (error("heredoc", "Failed to duplicate fd"));
	}
	else
	{
		tokens->here_fd = open(tokens->here_file, O_RDONLY);
		if (tokens->here_fd < 0)
			return (1);
		if (dup2(tokens->here_fd, STDIN_FILENO) == -1)
		{
			close(tokens->here_fd);
			return (error("heredoc", "Failed to duplicate fd"));
		}
		close(tokens->here_fd);
	}
	return (0);
}

int	parse_heredoc(char **args)
{
	int	i;

	i = -1;
	while (args[++i] != 0)
	{
		if (args[i] != 0 && ft_strncmp(args[i], "<<", 2) == 0)
		{
			i++;
			if (args[i] != 0)
				return (1);
		}
	}
	return (0);
}

void	here_exec(char *line, char *eof, t_tokens *tokens, t_data *data)
{
	line = readline("hereboy> ");
	if (line == NULL || (ft_strlen(line) == ft_strlen(eof)
			&& ft_strncmp(line, eof, ft_strlen(eof)) == 0))
	{
		line = free_string(line);
		close(tokens->here_fd);
		free_n_exit(data, 0, 0);
		tokens->here_file = free_string(tokens->here_file);
		exit(0);
	}
	write(tokens->here_fd, line, ft_strlen(line));
	write(tokens->here_fd, "\n", 1);
	line = free_string(line);
}

void	wait_and_close_2(pid_t	kido, int status, t_data *data)
{
	waitpid(kido, &status, 0);
	if (status > 0)
	{
		exit_code(1, 130);
		data->tokens->ignore_heredoc = true;
	}
	close(data->tokens->here_fd);
}

void	heredoc_loop(t_data *data, int status, t_tokens *tokens, char *eof)
{
	char		*line;
	pid_t		kido;

	kido = 0;
	line = NULL;
	tokens->here_file = free_string(tokens->here_file);
	tokens->here_file = ft_strdup("temp_heredoc_file_that_none_know_about");
	tokens->here_fd = 0;
	if (tokens->here_file != NULL)
		tokens->here_fd = open(tokens->here_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tokens->here_fd < 0)
		return ;
	kido = fork();
	if (kido == 0)
	{
		signal(SIGINT, here_signal);
		while (1)
			here_exec(line, eof, tokens, data);
	}
	wait_and_close_2(kido, status, data);
}
