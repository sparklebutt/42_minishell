/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_loopers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:08:22 by araveala          #+#    #+#             */
/*   Updated: 2025/07/09 16:07:05 by araveala         ###   ########.fr       */
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
