/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:12:21 by araveala          #+#    #+#             */
/*   Updated: 2024/06/08 17:19:00 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int insert_node(t_env **env_lst, char *key_name, char *value)
{
    t_env  *new_node;
    t_env  *tmp;

    new_node = malloc(sizeof(t_env));
    if (new_node == NULL)
        return (-1);
    new_node->key = key_name;
    new_node->value = value;
    new_node->next = NULL;
    if (*env_lst == NULL)
    {
        *env_lst = new_node;
        return (1);
    }
    tmp = *env_lst;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_node;
    return (1);
}

// void	remove_node(t_env *node)
// {
// 	// for unset 
// }

void	free_nodes(t_env *node)
{
	while ((*node).next != NULL)
	{
		free(node->value);
		free(node->key);
		node = node->next;
	}
}
