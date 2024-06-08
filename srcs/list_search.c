/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:05:37 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/08 19:58:32 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*move_list(t_env *envs, char *key)
{
	// do we need to combine all into data, we get very long lines ???
	t_env *temp;

	temp = envs;
	while (temp->next != NULL)// (1)
	{
		if (ft_strnstr(temp->key, key, ft_strlen(temp->key) + 1) && ft_strlen(temp->key) == ft_strlen(key))
			break ;
		temp = temp->next;
	}
	return (temp);
}

// finds the node with the key that matches the input key
int find_node(t_env *envs, char *key, t_data *data)
{
	// do we need to combine all into data, we get very long lines ???
	t_env *temp;
	
	if (!envs)
		return (0);
	temp = envs;
	while (temp->next != NULL)// (1)
	{
		// ft_printf("- - - - - - - - - - - - - - - - - - \n"); // remove
		// ft_printf("looking for key: %s|\n", key); // remove
		// ft_printf("temp->key: %s|\n", temp->key); // remove
		// ft_printf("temp->value: %s\n", temp->value); // places revious key as value???
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0 && (ft_strlen(temp->key) == ft_strlen(key)))
		{
//			ft_printf("found %s key from env!!\n", temp->key);
//			ft_printf("kay's value is: %s\n", temp->value);
			data->tmp->env_line = ft_strdup(temp->value);
			printf("aaaarg = %s\n", data->tmp->env_line);
			return (1);
		}
		temp = temp->next;
		if (temp->next == envs)
			break ;
	}
	ft_printf("key not found\n");
	return (0); // segfaults if not found, need to fix this
}
