/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 04:44:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/05 13:08:11 by vkettune         ###   ########.fr       */
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
			// create file here
			if (args[i] != 0) // check if there is a eof
				return (1);
		}
	}
	return (0);
}


// usage: heredoc_loop("eof"); 
//  note: clean quotes before adding eof to heredoc_loop
// e.g.: 
// 
// while (tokens->args[i])
// {
// 	if (ft_strncmp(tokens->args[i], "<<", 2) == 0)
// 		heredoc_loop(tokens->args[i + 1]);
// 	i++;
// }

char **set_into_heredoc_array(char **heredoc, char *line)
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
	new_heredoc[i] = ft_strdup(line);
	new_heredoc[i + 1] = 0;
	free(heredoc);
	return (new_heredoc);
}

void heredoc_loop(t_tokens *tokens, char *eof)
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
			free(line);
			break ;
		}
		tokens->heredoc = set_into_heredoc_array(tokens->heredoc, line);
		free(line);
	}
}

