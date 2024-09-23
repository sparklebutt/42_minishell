/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:10:09 by araveala          #+#    #+#             */
/*   Updated: 2024/09/23 11:29:52 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_collector(t_tokens *tokens, char **array)
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
			if (len == 2)
			{
				if (array[i][1] == '|')
					return (not_perror("syntax error", NULL, "unexpected token\n"), -1);
			}
			if (len > 2)
				if (array[i][2] == '|')
					return (not_perror("syntax error", NULL, "unexpected token\n"), -1);
			count++;
		}
		i++;
	}
	tokens->pipe_count = count;
	return (0);
}
