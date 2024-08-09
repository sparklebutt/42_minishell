/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:59:15 by araveala          #+#    #+#             */
/*   Updated: 2024/08/09 09:41:38 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_extra_return_function(char *str, int ret_value)
{
	free_string(str);
	return (ret_value);
}

void	free_array(char **array)
{
	int	i;

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
	if (string != NULL)
	{
		free(string);
		string = NULL;
	}
}

void	free_nodes(t_env *node)
{
	t_env	*tmp;

	while (node != NULL)
	{
		if (node->value)
			free(node->value);
		free(node->key);
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

int	error(char *cmd, char *error)
{
	ft_printf("minishell: %s: %s\n", cmd, error);
	return (1);
}

void	collective_free(char *str1, char *str2, char **array) // maybe not needed, will make function amount to be correct
{
	free_array(array);
	free_string(str1);
	free_string(str2);
	array = NULL;
	str1 = NULL;
	str2 = NULL;
}
