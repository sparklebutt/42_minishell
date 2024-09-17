/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 04:44:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/17 08:16:14 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_heredoc(char **args) // add more args
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
	while (heredoc[i] != NULL)
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
	int i;

	i = 0;
	fd = 0;
	// dprintf(2, "\t\tsteps into create file AS IT SHOULD\n");
	if (tokens->here_file != NULL)
		fd = open(tokens->here_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
	if (fd <= 0)
		return (error("redirect", "Failed to open input file B"));
	// if (dup2(fd, STDOUT_FILENO) == -1)
	// 	return (error("redirect", "Failed to duplicate fd"));
	// while (tokens->heredoc[i] != NULL)
	// {
	// 	printf("%s\n", tokens->heredoc[i]);
	// 	i++;
	// }
	// free_array(tokens->heredoc);
	close(fd);
	return (0);
}

void heredoc_loop(t_data *data, t_tokens *tokens, char *eof)
{
	char	*line = NULL;
	int fd = 0;

	tokens->h_action = true;
	tokens->here_file = ft_strdup("temp_heredoc_file_that_none_know_about");
	tokens->heredoc = malloc(sizeof(char *) * 1);
	tokens->heredoc[0] = NULL;
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		// printf("eof = |%s|, strlen = %zu\n", eof, ft_strlen(eof));
		// printf("line = |%s|, strlen = %zu\n", line, ft_strlen(line));
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0 && ft_strlen(eof) + 1 == ft_strlen(line))
		{
			line = free_string(line);
			break ;
		}
		tokens->heredoc = set_into_heredoc_array(data, tokens->heredoc, line);
		line = free_string(line);
	}
	create_file(data->tokens);
}
