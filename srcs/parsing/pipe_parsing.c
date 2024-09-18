/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:10:09 by araveala          #+#    #+#             */
/*   Updated: 2024/09/18 09:26:54 by vkettune         ###   ########.fr       */
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
			if (len == 2)
			{
				if (array[i][1] == '|')
					printf("we have 2 pipes next to eachother\n");
			}
			if (len > 2)
				if (array[i][2] == '|')
					printf("syntax error , too many pipes\n");
			count++;
		}
		i++;
	}
	tokens->pipe_count = count;
}
