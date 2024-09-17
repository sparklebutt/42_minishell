/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 04:44:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/17 13:28:20 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_and_fill_heredoc(t_tokens *tokens)
{
	int fd;
	int i;

	i = 0;
	fd = open(tokens->here_file, O_RDWR);
	if (fd < 0)
		return (error("heredoc", "Failed to open input file B"));
	if (dup2(fd, STDIN_FILENO) == -1) // if dupe fails we aren't closing fd's
		return (error("heredoc", "Failed to duplicate fd"));
	close(fd);
	while (tokens->heredoc[i] != NULL)
	{
		printf("%s\n", tokens->heredoc[i]);
		i++;
	}
	free_array(tokens->heredoc);
	return (0);
}

int parse_heredoc(char **args)
{
	int		i;

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

char **set_into_heredoc_array(t_data *data, char **heredoc, char *line)
{
	int		i;
	char	**new_heredoc;

	i = 0;
	while (heredoc[i] != 0)
		i++;
	new_heredoc = malloc(sizeof(char *) * (i + 2));
	if (new_heredoc == NULL)
		return (NULL);
	i = 0;
	while (heredoc[i] != NULL)
	{
		new_heredoc[i] = heredoc[i];
		i++;
	}
	ft_strlcpy(line, line, ft_strlen(line));
	if (ft_strchr(line, '$') != NULL)
		new_heredoc[i] = look_if_expansions(data, data->env, ft_strdup(line), 0);
	else
		new_heredoc[i] = ft_strdup(line);
	new_heredoc[i + 1] = NULL;
	free(heredoc);
	return (new_heredoc);
}

int create_file(t_tokens *tokens)
{
	int fd;

	fd = 0;
	if (tokens->here_file != NULL)
		fd = open(tokens->here_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
	if (fd <= 0)
		return (error("heredoc", "Failed to open input file A"));
	close(fd);
	return (0);
}

void heredoc_loop(t_data *data, t_tokens *tokens, char *eof)
{
	char	*line = NULL;
	int fd = 0;

	dprintf(2, "turning heredoc flag on\n");
	// tokens->h_action = true;
	tokens->here_file = ft_strdup("temp_heredoc_file_that_none_know_about");
	tokens->heredoc = malloc(sizeof(char *) * 1);
	tokens->heredoc[0] = NULL;
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0 && ft_strlen(eof) + 1 == ft_strlen(line))
		{
			free_string(line);
			break ;
		}
		tokens->heredoc = set_into_heredoc_array(data, tokens->heredoc, line);
		free_string(line);
	}
	create_file(data->tokens);
}
