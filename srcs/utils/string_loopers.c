/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_loopers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:08:22 by araveala          #+#    #+#             */
/*   Updated: 2024/09/21 21:21:43 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*exp_loop(char c, int *i, const char *s, int *count)
{
	s++;
	(*i)++;
	if (*s == c)
		(*count)++;
	while (*s && *s != c)
	{
		(*i)++;
		s++;
	}
	s++;
	(*count)++;
	return (s);
}

void	sublen_loop(char c, int *sublen, int *save, const char *s)
{
	(*save)++;
	(*sublen)++;
	while (s[*save] && s[*save] != c)
	{
		(*save)++;
		(*sublen)++;
	}
	(*save)++;
	(*sublen)++;
}

void	fancy_loop(const char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
}

void	stupid_if_statement(const char *s, int *i)
{
	if (s[*i] == '"' && (*i)++)
	{
		while (s[*i] && s[*i] != '"')
			(*i)++;
	}
	else if (s[*i] == '\'' && (*i)++)
	{
		while (s[*i] && s[*i] != '\'')
			(*i)++;
	}
	(*i)++;
}

void	close_diff_fds(int *fds, t_data *data, int flag)
{
	if (data->prev_fd != -1)
		close(data->prev_fd);
	close(fds[1]);
	if (flag == 2)
		data->prev_fd = fds[0];
	if (flag == 0)
		close(fds[0]);
}
