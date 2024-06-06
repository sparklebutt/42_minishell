/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:12:21 by araveala          #+#    #+#             */
/*   Updated: 2024/06/06 18:23:17 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *add_new_node(char *value_in, char *key_in)
{
    t_env *new;
    char *temp;
    char *temp2;

    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
    {
        printf("new node creation failure\n");
        return (0);
    }
    ft_printf("- - - - - - - - - \n"); // remove
    new->next = NULL;
    new->prev = NULL;
    new->key  = key_in;
    temp = ft_strtrim(value_in, key_in);
    temp2 = ft_strtrim(temp, "=");
    free(temp);
    new->value = temp2;
    return (new);
}

void    addnode(t_env **env_lst, t_env *node) //does not assign value correctly
{
    t_env *temp;

    if ((*env_lst)->key == NULL)
    {
        (*env_lst) = &(*node);
        return ;
    }
    temp = (*env_lst);
    while((*env_lst)->next != NULL)
        (*env_lst) = (*env_lst)->next;
    if ((*env_lst)->next == NULL)
    {
        (*env_lst)->next = (&(*node));
        (*node).prev = (*env_lst);
        (*env_lst)->next->next = NULL;
        (*env_lst)->prev = NULL;
        (*env_lst)->head = temp;
        *env_lst = (*env_lst)->head;
    }
}

/*void	remove_node()
{
	for unset 
	}*/

void	free_nodes(t_env *nodes)
{
	while ((*nodes).next != NULL)
	{
		free(nodes->value);
		free(nodes->key);
		free(nodes);
		nodes = nodes->next;
	}
}
