/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:17:27 by araveala          #+#    #+#             */
/*   Updated: 2024/08/08 11:46:54 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool confirm_expansion(char *string, int len)
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
/*	if (d == true)
		printf("d = treu\n");
	else if (d == false)
		printf("d = false\n");
	if (s == true)
		printf("s = treu\n");
	else if (s == false)
		printf("s = false\n");*/
	return ((d && !s) || (!d && !s));
}


/*~~ to find and confirm expansion , then to do expansion so we can pass a preped token array , there is nothing stopping us 
from instead using this code later down the line instead of being one of the first things we do ~~*/
void	expansion_parser(t_tokens *tokens, t_data *data)
{
	int i;
	int len;
	static char *new;
	
	i = 0;
	len = 0;
	while (tokens->args[i])
	{
		len = ft_strlen(tokens->args[i]) - 1;
/*~~ is this check for a dollar sign safe enough or are there special edge cases 
where our code might get confused and consider the $sign as valuable when it shouldnt ~~*/
		if (ft_strchr(tokens->args[i], '$') != NULL)
		{
			if (confirm_expansion(tokens->args[i], len) == true)
			{
				printf("expandable, we start expansion process and cleanin string first\n");
				if (ft_strchr(tokens->args[i], '"') != NULL || ft_strchr(tokens->args[i], '\'') != NULL)
				{
					new = clean_quotes(tokens->args[i], len);
					free_string(tokens->args[i]);
					tokens->args[i] = new;
					printf("args = %s\n", tokens->args[i]);
					tokens->args = variable_expansions(data, data->env, tokens->args);	
				}
				else
				{
					printf("why is it here?\n");
					tokens->args = variable_expansions(data, data->env, tokens->args);
					printf("why is it here?\n");
				}
					
			}
			else
			{
				printf("not expandable we only clean quotes\n");
				new = clean_quotes(tokens->args[i], len);
				free_string(tokens->args[i]);
				tokens->args[i] = new;
			}
		}
		i++;
/*~~ should we clean quotes here aswell or will this clean quotes too early,
having them here would mean quotes are cleaned before anything happens and this
could be good for testing but maybe too early for somethings (things unknow)~~*/
	}
}
