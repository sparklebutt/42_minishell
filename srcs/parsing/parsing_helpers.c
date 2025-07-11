/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:17:27 by araveala          #+#    #+#             */
/*   Updated: 2024/09/21 17:47:14 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	set_check(char *string, bool ver, int *x, char c)
{
	int	len;

	len = ft_strlen(string);
	(*x)++;
	while (string[*x] && string[*x] != c)
	{
		(*x)++;
		if (string[*x] == c)
			ver = !ver;
		if ((*x) == len - 1)
			break ;
	}
	return (ver);
}

int	simple_quote_check(char *s, int i)
{
	int	x;
	int	counter;

	counter = 0;
	x = i;
	while (s[x])
	{
		if (s[x] == '$')
		{
			if (s[x + 1] && s[x + 1] == ' ')
				return (-1);
			counter++;
		}
		x++;
	}
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] == '\'' || (s[i + 1] == '"')
				|| (counter < 2 && s[i + 1] == '$')))
			return (-1);
		if (s[i] == '$' && counter < 2 && i == 0)
			return (0);
		i++;
	}
	return (1);
}

bool	confirm_expansion(char *string, int len, int x)
{
	bool	s;
	bool	d;
	int		simple_ret;

	s = false;
	d = false;
	simple_ret = simple_quote_check(string, x);
	if (simple_ret == -1)
		return (false);
	if (simple_ret == 0)
		return (true);
	while (string[x] && x < len)
	{
		if (string[x] == '\'')
			s = set_check(string, s, &x, '\'');
		else if (string[x] == '"')
			d = set_check(string, d, &x, '"');
		x++;
	}
	return ((d && !s) || (!d && !s));
}

int	multi_dollar_handle(t_data *data, t_tokens *tokens, int i)
{
	int			index;
	size_t		len;
	static char	*new;

	len = 0;
	index = 0;
	data->simple = false;
	data->tmp->exp_array = ft_split_expansions(tokens, tokens->args[i], 0);
	if (data->tmp->exp_array == NULL)
		return (not_perror("parsing", NULL, "malloc fail\n"), -1);
	while (data->tmp->exp_array[index] != NULL)
	{
		len = ft_strlen(data->tmp->exp_array[index]);
		if (confirm_expansion(data->tmp->exp_array[index], len, 0) == true)
			handle_expansion(data, len - 1, index, new);
		else
			clean_rest_of_quotes(data, index, len);
		index++;
	}
	return (0);
}
