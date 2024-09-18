/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_loopers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:08:22 by araveala          #+#    #+#             */
/*   Updated: 2024/09/18 14:58:10 by vkettune         ###   ########.fr       */
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

int	loop_quotes(t_tokens *tokens, int quote_count, int i, int *x)
{
	char	c;

	c = 0;
	if (tokens->quote == 1)
		c = '\'';
	else if (tokens->quote == 2)
		c = '"';
	(*x)++;
	quote_count += 1;
	if (tokens->args[i][*x] == c)
		quote_count += 1;
	while (tokens->args[i][*x] != '\0' && tokens->args[i][*x] != c)
	{
		(*x)++;
		if (tokens->args[i][*x] == c)
			quote_count += 1;
	}
	return (quote_count);
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
