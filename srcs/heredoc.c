/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 04:44:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/10 12:52:07 by vkettune         ###   ########.fr       */
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
	while (heredoc[i] != 0)
		i++;
	new_heredoc = malloc(sizeof(char *) * (i + 2));
	if (new_heredoc == NULL)
		return (NULL);
	i = 0;
	while (heredoc[i] != 0)
	{
		new_heredoc[i] = heredoc[i];
		i++;
	}
	ft_strlcpy(line, line, ft_strlen(line));
	if (ft_strchr(line, '$') != NULL)
		new_heredoc[i] = look_if_expansions(data, data->env, ft_strdup(line), 0);
	else
		new_heredoc[i] = ft_strdup(line);
	new_heredoc[i + 1] = 0;
	free(heredoc);
	return (new_heredoc);
}


void heredoc_loop(t_data *data, t_tokens *tokens, char *eof)
{
	char	*line = NULL;
	int fd = 0;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0)
		{
			free_string(line);
			break ;
		}
		tokens->heredoc = set_into_heredoc_array(data, tokens->heredoc, line);
		free_string(line);
	}
}
