/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 04:44:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/24 16:48:41 by vkettune         ###   ########.fr       */
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
		printf("beep boop\n");
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

// int	open_and_fill_heredoc(t_tokens *tokens)
// {
// 	tokens->here_fd = open(tokens->here_file, O_RDONLY);
// 	if (tokens->here_fd < 0)
// 		return (1);
// 	if (dup2(tokens->here_fd, STDIN_FILENO) == -1)
// 	{
// 		close(tokens->here_fd);
// 		return (error("heredoc", "Failed to duplicate fd"));
// 	}
// 	close(tokens->here_fd);
// 	free_array(tokens->heredoc);
// 	tokens->heredoc = NULL;
// 	return (0);
// }

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

// char	**set_into_heredoc_array(t_data *data, char **heredoc, char *line)
// {
// 	int		i;
// 	char	**new_heredoc;

// 	new_heredoc = NULL;
// 	i = 0;
// 	while (heredoc != NULL && heredoc[i] != 0)
// 		i++;
// 	if (i == 0)
// 		i++;
// 	new_heredoc = ft_calloc(sizeof(char *), (i + 2));
// 	if (new_heredoc == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (heredoc != NULL && heredoc[i] != NULL)
// 		stupid_function_4(new_heredoc, heredoc, &i);
// 	new_heredoc[i] = set_the_string(data, line);
// 	if (new_heredoc[i] != NULL)
// 		new_heredoc[i + 1] = NULL;
// 	free_array(heredoc);
// 	heredoc = NULL;
// 	return (new_heredoc);
// }

int	create_file(t_tokens *tokens)
{
	int	i;

	i = 0;
	tokens->here_fd = 0;
	if (tokens->here_file != NULL)
		tokens->here_fd = open(tokens->here_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tokens->here_fd < 0)
		return (error("heredoc", "Failed to open input file A"));
	// while (tokens->heredoc != NULL && tokens->heredoc[i] != NULL)
	// {
	// 	write(tokens->here_fd, tokens->heredoc[i],
	// 		ft_strlen(tokens->heredoc[i]));
	// 	i++;
	// }
	// close(tokens->here_fd);
	return (0);
}

void    heredoc_loop(t_data *data, int status, t_tokens *tokens, char *eof)
{
	char	*line;
	pid_t	kido;
	// int		status;
	
	kido = 0;
	// status = 0;
	(void)data;
	line = NULL;
	tokens->here_file = ft_strdup("temp_heredoc_file_that_none_know_about");
	// create_file(tokens);
	tokens->here_fd = 0;
	if (tokens->here_file != NULL)
		tokens->here_fd = open(tokens->here_file,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tokens->here_fd < 0)
		return ; //exit and clean
	kido = fork();
	if (kido == 0)
	{
		signal(SIGINT, here_signal);
		while (1)
		{
			line = readline("hereboy> ");    
			if (line == NULL || (ft_strlen(line) == ft_strlen(eof)
				&& ft_strncmp(line, eof, ft_strlen(eof)) == 0))
			{
				dprintf(2, "IT STEPS IN HERE 22222\n");
				line = free_string(line);
				close(tokens->here_fd);
				free_n_exit(data, 0, 0); // tokens->here_file = free_string(tokens->here_file);
				exit(0);
			}
			write(tokens->here_fd, line, ft_strlen(line));
			write(tokens->here_fd, "\n", 1);
			line = free_string(line);    
		}
		close(tokens->here_fd);
	}
	waitpid(kido, &status, 0);
	dprintf(2, "AAAAAAAAAAAAAA\n");
	if (status > 0)
	{
		dprintf(2, "IT STEPS IN HERE 11111111111\n");
		close(tokens->here_fd);
		exit_code(1, 130);
		data->tokens->ignore_heredoc = true;
		// free_n_exit(data, 0, 0); 
	}
	printf("staus = %d\n", status = (status >> 8) & 0xFF);
	close(tokens->here_fd);
	
	// free_stuff(data, 1);
}

// void	heredoc_loop(t_data *data, t_tokens *tokens, char *eof)
// {
// 	char	*line;
// 	int		fd;

// 	fd = 0;
// 	line = NULL;
// 	tokens->here_file = ft_strdup("temp_heredoc_file_that_none_know_about");
// 	signal(SIGINT, here_signal);
// 	while (1)
// 	{
// 		if (g_interactive_mode == 1)
// 		{
// 			g_interactive_mode = 0;
// 			break ;
// 		}
// 		line = readline("hereboy> ");
// 		if (line == NULL || (ft_strlen(line) == ft_strlen(eof)
// 				&& ft_strncmp(line, eof, ft_strlen(eof)) == 0))
// 		{
// 			line = free_string(line);
// 			break ;
// 		}
// 		tokens->heredoc = set_into_heredoc_array(data, tokens->heredoc, line);
// 		line = free_string(line);
// 	}
// 	signal(SIGINT, signal_handler);
// 	create_file(data->tokens);
// }
