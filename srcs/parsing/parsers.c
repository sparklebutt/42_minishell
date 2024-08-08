/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:17:27 by araveala          #+#    #+#             */
/*   Updated: 2024/08/08 15:31:12 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool confirm_expansion(char *string, int len) // similar to quotes_handling (combine them?), maybe add bools into struct
{
	bool s;
	bool d;
	int x;
	s = false;
	d = false;
	
	x = 0;
	while (x <= len) 
	{
		if (string[x] == '\'')
		{
			x++;
			while (string[x] != '\'')
			{
				s = !s;
				x++;
			}
		}
		else if (string[x] == '"')
		{
			x++;
			while (string[x] != '"')
			{
				d = !d;
				x++;
			}		
		}
		x++;
	}
	return ((d && !s) || (!d && !s));
}

void	expansion_parser(t_tokens *tokens, t_data *data)
{
	int i;
	int len;
	static char *new;
	
	i = 0;
	len = 0;
	while (tokens->args[i])
	{
		len = ft_strlen(tokens->args[i]) - 1; // maybe remove
		if (ft_strchr(tokens->args[i], '$') != NULL)
		{
			if (confirm_expansion(tokens->args[i], len) == true)
			{
				// tokens->args[i] = expand_args(tokens->args[i], data, data->env) // add something like this
				if (ft_strchr(tokens->args[i], '"') != NULL || ft_strchr(tokens->args[i], '\'') != NULL)
				{
					new = clean_quotes(tokens->args[i], len);
					free_string(tokens->args[i]);
					tokens->args[i] = look_if_expansions(data, data->env, new);
				}
				else
					tokens->args[i] = look_if_expansions(data, data->env, tokens->args[i]);
			}
			else
			{
				new = clean_quotes(tokens->args[i], len);
				free_string(tokens->args[i]);
				tokens->args[i] = new;
			}
		}
		i++;
	}
}

// void parse_redirections(t_tokens *tokens)
// {
// 	(void)tokens;
// }
