/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:17:27 by araveala          #+#    #+#             */
/*   Updated: 2024/07/02 15:15:12 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// by calling this fucntion straight away, we dont have to worry about this anymore
int	check_open_quotes(t_tokens *tokens)
{
	int x;
	int i;
	int s_quote_count;
	int d_quote_count;

	x = 0;
	i = 0;
	s_quote_count = 0;
	d_quote_count = 0;
	ft_printf("weep before me\n");
	while (tokens->args[i])
	{
		while (tokens->args[i][x] != '\0')
		{
			if (tokens->args[i][x] == 39)
				s_quote_count += 1;
			else if (tokens->args[i][x] == 34)
				d_quote_count += 1;
			x++;
		}
		i++;
	}
	if (s_quote_count % 2 != 0 || d_quote_count % 2 != 0)
	{
		ft_printf("unclosed quotes , must open the wierd propmt\n");
		ft_printf("function check_open_quotes in parsers.c, called in collect_cmd_array\n");
		return (-1); // error
	}
	return (1);
}

void	pipe_collector(t_tokens *tokens, char **array)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;

	while (array[i])
	{
		len = ft_strlen(array[i]);
		if (array[i][0] == '|')
		{
			ft_printf("array[i][0] is a pipe\n");
			// ft_printf("counting irrelevant piupes , that bad \n");
			if (len == 2)
			{
				if (array[i][1] == '|')
					printf("we have 2 pipes next to eachother BONUS POTENTIAL\n");
				// we can do a count and mark special char for bonuse here
			}
			if (len > 2)
			{
				if (array[i][2] == '|')
					printf("syntax error , too many pipes STEP BACK TO MAIN\n");
			}
			count++;
			// splt already confirmed spaces around pipe
			// pipe as last char needs to be handled
		}
		i++;
	}
	tokens->pipe_count = count;
	// printf("we have %d pipes\n", tokens->pipe_count);
}

void	expansion_parser(t_tokens *tokens)
{
	int i;
	int x;
	
	i = 0;
	x = 0;
	// no open quotes, this is already checked before this in collect_cmd_array
	while (tokens->args[i])
	{
		ft_printf("TOKEN = %s\n", tokens->args[i]);
		if (ft_strchr(tokens->args[i], '$') != NULL)
		{
			while (tokens->args[i][x] != '$') // do we need to check null here?
				x++;
			if (tokens->args[i][x - 1] == 39 || tokens->args[i][0]) // before dollar sign
			{
				ft_printf("remove ALL single quotes, handle as string no meta data\n");
			}
			else if (tokens->args[i][x - 1] == 34 && tokens->args[i][x + 1] != 34)
			{
				ft_printf("expand and remove double quotes\n");
			}
		}
		else
			mini_quote_parser(tokens , i);
//				x++;			
		i++;
	}
}

void	mini_quote_parser(t_tokens *tokens, int i)
{
	int x;

	x = 0;
	while (tokens->args[i][x] != '\0')
	{
		if (tokens->args[i][x] == 39)//single quotes
		{			
			ft_printf("holding single quote\n");
		}
		x++;
	}
}

void	mini_parser(t_tokens *tokens, int i, int x)
{
	// char	*tmp;

	// tmp = NULL;
	while (i != x)
	{
		if (ft_strncmp(tokens->args[i], "CD", 2) == 0)
		{
			printf("is it big = %s\n", tokens->args[i]);
			printf("oho CD , WILL THIS HELP ? (min_parser in parsers.c)\n");

			/*tmp = tokens->args[i];
			free_string(tokens->args[i]);
			cmd_to_lower(tmp);
			tokens->args[i] = tmp;
			printf("did it get smaller = %s\n", tokens->args[i]);
			 free_string(args[i]);*/

			// some error handling maybe?
		}
		i++;
	}
}
