/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:10:09 by araveala          #+#    #+#             */
/*   Updated: 2024/07/03 17:10:50 by araveala         ###   ########.fr       */
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
