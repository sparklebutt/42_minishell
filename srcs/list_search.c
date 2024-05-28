/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:05:37 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/28 16:42:40 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*move_list(t_env *envs, char *key)
{
	// do we need to combine all into data, we get very long lines ???
	t_env *temp;

	temp = envs;
	while (temp->prev != NULL)// (1)
	{
		if (ft_strnstr(temp->key, key, ft_strlen(temp->key) + 1) && ft_strlen(temp->key) == ft_strlen(key))
			break ;
		temp = temp->prev;
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
	while (temp->prev != NULL)// (1)
	{
//		ft_printf("- - - - - - - - - - - - - - - - - - \n"); // remove
//		ft_printf("looking for key: %s|\n", key); // remove
//		ft_printf("temp->key: %s|\n", temp->key); // remove
//		ft_printf("temp->value: %s\n", temp->value); // places revious key as value???
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0 && (ft_strlen(temp->key) == ft_strlen(key)))
		{
//			ft_printf("found %s key from env!!\n", temp->key);
//			ft_printf("kay's value is: %s\n", temp->value);
			data->tmp->env_line = ft_strdup(temp->value);
			printf("aaaarg = %s\n", data->tmp->env_line);
			return (0);
		}
		temp = temp->prev;
		// temp = temp->next;
		// temp->value = temp->prev->value;
		// temp->key = temp->prev->key;
		if (temp->prev == envs)
			break ;
	}

	ft_printf("key not found\n");
	return (1); // segfaults if not found, need to fix this
}


// int find_node(t_env *envs, char *key) 
// {
// 	t_env *temp;

// 	if (!envs || !key) {
// 			return 0;
// 	}
// 	temp = envs;
// 	printf("envs->value: %s\n", envs->value);
// 	printf("temp->value: %s\n", temp->value); // correct value
// 	while (temp != NULL) {
// 			printf("- - - - - - - - - - - - - - - - - - \n");
// 			printf("looking for key: %s|\n", key); // remove
// 			printf("temp->key: %s|\n", temp->key); // remove
// 			printf("temp->value: %s\n", temp->value); // places previous key as value???
// 			if (temp->prev != NULL) {
// 					printf("temp->prev->value: %s\n", temp->prev->value); // remove
// 					printf("temp->prev->key: %s\n", temp->prev->key); // remove
// 			} else {
// 					printf("temp->prev is NULL\n"); // remove
// 			}
// 			if (strncmp(temp->key, key, strlen(key)) == 0 && strlen(temp->key) == strlen(key)) {
// 					printf("found key: %s\n", temp->key);
// 					printf("found value: %s\n", temp->value);
// 					return 1;
// 			}
// 			temp = temp->next;
// 	}
// 	printf("key not found\n");
// 	return 0;
// }
