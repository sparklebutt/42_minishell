/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:55:36 by araveala          #+#    #+#             */
/*   Updated: 2024/08/08 14:44:03 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

// 3 functions in here , check for open quotes, count new len based on quotes and create a new string with quotes removed

// by calling this fucntion straight away, we dont have to worry about this anymore
int	check_open_quotes(t_tokens *tokens)
{
	int	x;
	int	i;
	int	s_quote_count;
	int	d_quote_count;

	x = 0;
	i = 0;
	s_quote_count = 0;
	d_quote_count = 0;
	while (tokens->args[i])
	{
		while (tokens->args[i][x] != '\0')
		{
			if (tokens->args[i][x] == '\'')
			{
				x++;
				s_quote_count += 1;
				while (tokens->args[i][x] != '\0' && tokens->args[i][x] != '\'')
				{
					x++;
					if (tokens->args[i][x] == '\'')
						s_quote_count += 1;

				}
			}
			else if (tokens->args[i][x] == '"')
			{
				x++;
				d_quote_count += 1;
				while (tokens->args[i][x] != '\0' && tokens->args[i][x] != '"')
				{
					x++;
					if (tokens->args[i][x] == '"')
						d_quote_count += 1;
				}
			}
			x++;
		}
		if (s_quote_count % 2 != 0 || d_quote_count % 2 != 0)
		{
//			printf("s_quote_count = %d\n", s_quote_count);
//			printf("d_quote_count = %d\n", d_quote_count);		
//			printf("probem is here \n");
			return (-1); // error
		}
		i++;
		x = 0;
	}
	return (1);
}
/*int	check_open_quotes(t_tokens *tokens)
{
	int	x;
	int	i;
	int	s_quote_count;
	int	d_quote_count;

	x = 0;
	i = 0;
	s_quote_count = 0;
	d_quote_count = 0;
	while (tokens->args[i])
	{
		while (tokens->args[i][x] != '\0')
		{
			if (tokens->args[i][x] == '\'')
				s_quote_count += 1;
			else if (tokens->args[i][x] == '"')
				d_quote_count += 1;
			x++;
		}
		if (s_quote_count % 2 != 0 || d_quote_count % 2 != 0)
		{
			ft_printf("unclosed quotes, wierd propmt, or syntax error\n");
			ft_printf("function check_open_quotes in parsers.c, called in collect_cmd_array\n");
			return (-1); // error
		}
		i++;
		x = 0;
	}
	return (1);
	}*/

// we count the new length of the string we want to create when we remove unwanted quotes
int count_new_len(char *string) //get new line length)
{
// this gives us the length of string to malloc after quotes removal
	int x;
	int len;

	x = -1;
	len = 0;
	while (x++ && string[x] != '\0') // x is important first here
	{
		if (string[x] == '\'')
		{
			x++;
			while (string[x] != '\'' && x++)
				len++;
			len--;
		}
		else if (string[x] == '"')
		{
			x++;
			while (string[x] != '"' && x++)
				len++;
			len--;
		}
		len++;
	}
	return (len);	
}

// creates a new string with unwanted quotes removed and returns the string
char *clean_quotes(char *string, int len)
{
	char *new;
	int x;
	int y;
	int def_len;

	y = 0;
	x = 0;
	def_len = ft_strlen(string);
	new = NULL;
	new = ft_calloc(len + 1, 1);
	if (new == NULL)
	{
		return (NULL);
	}
	while (x <= len)
	{
		if (string[x] == '\'')
		{
			x++;
			while (string[x] != '\'')
			{
				new[y] = string[x];
				y++;
				x++;
			}
		}
		else if (string[x] == '"')
		{
			x++;
			while (string[x] != '"')
			{
				new[y] = string[x];
				y++;
				x++;
			}		
		}
		x++;
		if (string[x] != '\'' && string[x] != '"')
		{
			new[y] = string[x];
			y++;
		}
	}
	return (*&new);
}
