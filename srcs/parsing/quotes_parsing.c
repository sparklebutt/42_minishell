/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:55:36 by araveala          #+#    #+#             */
/*   Updated: 2024/09/21 13:44:49 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_open_quotes(t_tokens *tokens, int s_quote_count, int d_quote_count)
{
	int	x;
	int	i;

	i = -1;
	while (tokens->args[i + 1] != NULL && tokens->args[++i])
	{
		x = 0;
		while (tokens->args[i][x] != '\0')
		{
			if (tokens->args[i][x] == '\'')
				stupid_function_3(tokens, &s_quote_count, i, &x);
			else if (tokens->args[i][x] == '"')
			{
				tokens->quote = 2;
				if ((int)ft_strlen(tokens->args[i]) > 1)
					d_quote_count = loop_quotes(tokens, d_quote_count, i, &x);
			}
			x++;
		}
		if (s_quote_count % 2 != 0 || d_quote_count % 2 != 0)
			return (not_perror("syntax error", NULL, "open quotes\n"), -1);
	}
	return (1);
}

void	help_clean_quotes(char *new, char *string, int *x, int *y)
{
	if (string[*x] == '\'')
	{
		(*x)++;
		while (string[*x] && string[*x] != '\'')
			new[(*y)++] = string[(*x)++];
	}
	else if (string[*x] == '"')
	{
		(*x)++;
		while (string[*x] && string[*x] != '"')
			new[(*y)++] = string[(*x)++];
	}
}

char	*clean_quotes(char *string, int len, int x, int y)
{
	char	*new;
	int		full_len;

	full_len = ft_strlen(string);
	new = ft_calloc(full_len + 1, 1);
	if (new == NULL)
		return (NULL);
	if (len == 0)
		len = ft_strlen(string);
	while (x <= len)
	{
		help_clean_quotes(new, string, &x, &y);
		if (string[x] == '$' && (string[x + 1] == '\'' || string[x + 1] == '"'))
			x++;
		if (string[x] != '\'' && string[x] != '"')
			new[y++] = string[x];
		x++;
		if (x == len)
			break ;
	}
	return (*&new);
}

// should work without quote check, but if it breaks the add it back
int	clean_rest_of_quotes(t_data *data, int i, int len)
{
	char	*new;

	new = NULL;
	if (data->simple == false
		&& data->tmp->exp_array && data->tmp->exp_array[i])
	{
		new = clean_quotes(data->tmp->exp_array[i], len, 0, 0);
		data->tmp->exp_array[i] = free_string(data->tmp->exp_array[i]);
		data->tmp->exp_array[i] = new;
	}
	else if (data->tokens->args[i] != NULL)
	{
		new = clean_quotes(data->tokens->args[i], len, 0, 0);
		data->tokens->args[i] = free_string(data->tokens->args[i]);
		data->tokens->args[i] = new;
	}
	return (0);
}
