/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:59:15 by araveala          #+#    #+#             */
/*   Updated: 2024/09/18 14:46:09 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_loop(char **arr, int index)
{
	while (--index)
		arr[index] = free_string(arr[index]);
	free(arr);
	return (NULL);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		array[i] = free_string(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

char	*free_string(char *string)
{
	if (string != NULL)
	{
		free(string);
	}
	return (NULL);
}

void	free_nodes(t_env *node)
{
	t_env	*tmp;

	while (node != NULL)
	{
		if (node->value)
			node->value = free_string(node->value);
		node->key = free_string(node->key);
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

int	error(char *cmd, char *error)
{
	exit_code(1, 1);
	ft_printf("minishell: %s: %s\n", cmd, error);
	return (1);
}
