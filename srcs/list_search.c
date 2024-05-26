/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:05:37 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/26 12:58:20 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*move_list(t_env *envs, char *key)
{
	t_env *temp;

	temp = envs;
	while (1)
	{
		// ft_printf("looking for key: %s|\n", key); // remove
		// ft_printf("temp->key: %s|\n", temp->key); // remove
		if (ft_strnstr(temp->key, key, ft_strlen(temp->key) + 1) && ft_strlen(temp->key) == ft_strlen(key))
			break ;
		temp = temp->prev;
	}
	return (temp);
}

// finds the node with the key that matches the input key
int find_node(t_env *envs, char *key)
{
	t_env *temp;
	

	if (!envs)
		return (0);
	temp = envs;
	ft_printf("envs->value: %s\n", envs->value);
	ft_printf("temp->value: %s\n", temp->value); // correct value
	while (1)
	{
		ft_printf("- - - - - - - - - - - - - - - - - - \n");
		ft_printf("looking for key: %s|\n", key); // remove
		ft_printf("temp->key: %s|\n", temp->key); // remove
		ft_printf("temp->value: %s\n", temp->value); // places revious key as value???
		// if (temp->next == NULL)
		// 	break ;
		// ft_printf("temp->prev->value: %s\n", temp->next->value); // remove
		// ft_printf("temp->prev->key: %s\n", temp->next->key); // remove
		temp = temp->prev;
		// if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) && ft_strlen(temp->key) == ft_strlen(key))
		// {
		// 	ft_printf("found key: %s\n", temp->key);
		// 	ft_printf("found value: %s\n", temp->value);
		// 	return (0);
		// }
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