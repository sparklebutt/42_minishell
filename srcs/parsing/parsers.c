/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:17:27 by araveala          #+#    #+#             */
/*   Updated: 2024/08/09 13:34:25 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	set_check(char *string, bool ver, int *x, char c)
{
	(*x)++;
	while (string[*x] != c)
	{
		ver = !ver;
		(*x)++;
	}
	return (ver);
}

// similar to quotes_handling (combine them?), maybe add bools into struct
bool	confirm_expansion(char *string, int len)
{
	bool	s;
	bool	d;
	int		x;

	s = false;
	d = false;
	x = 0;
	while (x <= len)
	{
		if (string[x] == '\'')
			s = set_check(string, s, &x, '\'');
		else if (string[x] == '"')
			d = set_check(string, d, &x, '"');
		x++;
	}
	return ((d && !s) || (!d && !s));
}

void	handle_expansion(t_data *data, int len, int i, char *new)
{
	t_tokens	*tokens;

	tokens = data->tokens;
	if (ft_strchr(tokens->args[i], '"') != NULL
		|| ft_strchr(tokens->args[i], '\'') != NULL)
	{
		new = clean_quotes(tokens->args[i], len, 0, 0);
		free_string(tokens->args[i]);
		tokens->args[i] = look_if_expansions(data, data->env, new);
	}
	else
		tokens->args[i] = look_if_expansions(data, data->env, tokens->args[i]);
}

void	expansion_parser(t_tokens *tokens, t_data *data)
{
	int			i;
	int			len;
	static char	*new;

	i = 0;
	len = 0;

	while (tokens->args[i])
	{
		len = ft_strlen(tokens->args[i]) - 1; // maybe remove
		if (ft_strchr(tokens->args[i], '$') != NULL)
		{
			if (confirm_expansion(tokens->args[i], len) == true)
			{
				printf("expansion true\n");
				// tokens->args[i] = expand_args(tokens->args[i], data,data->env)
				// add something like this
				handle_expansion(data, len, i, new);
			}
			else
			{
				printf("expansion false\n");
				new = clean_quotes(tokens->args[i], len, 0, 0);
				free_string(tokens->args[i]);
				tokens->args[i] = new;
			}
		}
		i++;
	}
}
