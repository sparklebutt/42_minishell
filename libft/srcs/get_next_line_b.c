/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:07:32 by araveala          #+#    #+#             */
/*   Updated: 2024/09/21 10:02:49 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_b.h"
#include <stdio.h>

char	*build_line(char *buffer, char *line)
{
	char	*the_line;

	if (!buffer || !*buffer)
	{
		free_string_b(&line);
		return (NULL);
	}
	if (line == NULL)
	{
		line = ft_calloc_b(1);
		if (line == NULL)
			return (NULL);
	}
	the_line = ft_strjoin_b(line, buffer);
	free_string_b(&line);
	return (the_line);
}

char	*get_the_line(char *line)
{
	char	*the_line;
	int		count;
	int		i;

	i = -1;
	count = nl_len(line, 0);
	if (count == -1)
		count = nl_len(line, 1) - 1;
	the_line = ft_calloc_b(count + 2);
	if (the_line == NULL)
		return (NULL);
	while (i++ < count)
		the_line[i] = line[i];
	return (the_line);
}

char	*get_left_overs(char *str)
{
	int		i;
	char	*temp;

	i = nl_len(str, 0);
	if (i == -1)
	{
		free_string_b(&str);
		return (NULL);
	}
	i = i + 1;
	temp = ft_strdup_b(str, i);
	free_string_b(&str);
	return (temp);
}

char	*read_to_line(char *buffer, char *s_line, int read_len)
{
	if (read_len == -1)
	{
		free_string_b(&s_line);
		return (NULL);
	}
	buffer[read_len] = '\0';
	if (*buffer != '\0' && *buffer)
		s_line = build_line(buffer, s_line);
	if (s_line == NULL)
		return (NULL);
	if (read_len == 0 && *buffer == '\0' && *s_line == '\0')
	{
		free_string_b(&s_line);
		return (NULL);
	}
	return (s_line);
}

char	*get_next_line(int fd)
{
	static char	*s_line = NULL;
	static char	buffer[BUFFER_SIZE + 1];
	char		*final_line;
	int			read_len;

	read_len = 0;
	while (BUFFER_SIZE > 0 && fd >= 0)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		s_line = read_to_line(buffer, s_line, read_len);
		if (s_line == NULL)
			return (NULL);
		if (nl_len(s_line, 0) > -1 || (read_len == 0 && s_line != NULL))
		{
			final_line = get_the_line(s_line);
			s_line = get_left_overs(s_line);
			if (final_line == NULL)
				free_string_b(&s_line);
			return (final_line);
		}
	}
	free_string_b(&s_line);
	return (NULL);
}
