/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:55:36 by araveala          #+#    #+#             */
/*   Updated: 2024/08/09 09:17:23 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_open_quotes(t_tokens *tokens)
{
	int	x;
	int	i;
	int	s_quote_count;
	int	d_quote_count;
	//x = 0; //not needed
	i = -1;
	s_quote_count = 0;
	d_quote_count = 0;
	while (tokens->args[++i])
	{
		x = 0;
		while (tokens->args[i][x] != '\0')
		{
			if (tokens->args[i][x] == '\'')
			{
				x++;
				s_quote_count += 1;
				if (tokens->args[i][x] == '\'')
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
				if (tokens->args[i][x] == '"')
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
			return (-1);
	//	x = 0;	
	
	}
	return (1);
}

int count_new_len(char *string)
{
	int x;
	int len;

	x = -1;
	len = 0;
	while (x++ && string[x] != '\0')
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
		return (NULL);
	while (x <= len)
	{
		if (string[x] == '\'')
		{
			x++;
			while (string[x] != '\'')
				new[y++] = string[x++];
		}
		else if (string[x] == '"')
		{
			x++;
			while (string[x] != '"')
				new[y++] = string[x++];	
		}
		if (string[x] != '\'' && string[x] != '"')
			new[y++] = string[x];
		x++;	
	}
	return (*&new);
}
