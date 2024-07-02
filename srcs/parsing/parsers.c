/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:17:27 by araveala          #+#    #+#             */
/*   Updated: 2024/07/01 17:42:25 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_collector(t_tokens *tokens, char **array)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (array[i]) // != '\0')
	{
		len = ft_strlen(array[i]);
		if (array[i][0] == '|')
		{
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
