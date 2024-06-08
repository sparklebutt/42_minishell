/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:59:15 by araveala          #+#    #+#             */
/*   Updated: 2024/06/08 19:44:49 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	if (array != NULL)
	{
		free(array);
		array = NULL;
	}
}

void	free_string(char *string)
{
	if (string)
	{
		free(string);
		string = NULL;
	}
}

int error(char *cmd, char *error)
{
	ft_printf("minishell: %s: %s\n", cmd, error);
	return (1);
}

void	free_nodes(t_env *node)
{
	while ((*node).next != NULL)
	{
		free(node->value);
		free(node->key);
		node = node->next;
	}
}
