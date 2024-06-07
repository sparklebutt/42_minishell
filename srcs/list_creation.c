/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:12:21 by araveala          #+#    #+#             */
/*   Updated: 2024/06/07 13:50:19 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_env *add_new_node(char *value_in, char *key_in)
// {
//     t_env *new;
//     char *temp;
//     char *temp2;

//     new = (t_env *)malloc(sizeof(t_env));
//     if (!new)
//     {
//         printf("new node creation failure\n");
//         return (0);
//     }
//     ft_printf("- - - - - - - - - \n"); // remove
//     new->next = NULL;
//     // new->prev = NULL;
//     new->key  = key_in;
//     temp = ft_strtrim(value_in, key_in);
//     temp2 = ft_strtrim(temp, "=");
//     free(temp);
//     new->value = temp2;
//     return (new);
// }

// void    addnode(t_env **env_lst, t_env *node) //does not assign value correctly
// {
//     t_env *temp;

// 		// temp = (*env_lst);
//     if ((*env_lst)->key == NULL)
//     {
//         (*env_lst) = &(*node);
// 				(*env_lst)->head = (*env_lst);
//         return ;
//     }
//     temp = (*env_lst);
// 		ft_printf("env->key: %s\n", temp->key); // remove
// 		ft_printf("env->value: %s\n", temp->value); // remove
// 		ft_printf("node->key: %s\n", node->key); // remove
// 		ft_printf("node->value: %s\n", node->value); // remove
// 		ft_printf("test\n"); // remove
// 		ft_printf("env->head: %s\n", temp->head->key); // remove
//     while(temp->next != NULL)
//         temp = temp->next;
//     if (temp->next == NULL)
//     {
//         temp->next = (&(*node));
//         // (*node).prev = (*env_lst);
//         temp->next->next = NULL;
//         // (*env_lst)->prev = NULL;
//         temp->head = temp;
//         // *env_lst = (*env_lst)->head;
//     }
// }

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

/*void	remove_node()
{
	for unset 
	}*/

void	free_nodes(t_env *nodes)
{
	while ((*nodes).next != NULL)
	{
		// free(nodes->value);
		// free(nodes->key);
		free(nodes);
		nodes = nodes->next;
	}
}
