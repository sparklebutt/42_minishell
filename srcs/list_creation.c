/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:12:21 by araveala          #+#    #+#             */
/*   Updated: 2024/05/26 13:03:07 by vkettune         ###   ########.fr       */
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
	new->key  = key_in;
	ft_printf("key: %s\n", new->key); // remove
	temp = ft_strtrim(value_in, key_in);
	temp2 = ft_strtrim(temp, "=");
	free(temp);
	new->value = temp2;
	free(temp2);
	ft_printf("value: %s\n", new->value); // remove
	new->prev = NULL;
	return (new);
}

void	addnode(t_env **env_lst, t_env *node) //does not assign value correctly
{
	t_env *temp;

	temp = (*env_lst);
	ft_printf("AAAAA node->key: %s\n", node->key); // remove
	ft_printf("AAAAA node->value: %s\n", node->value); // remove
	while ((*env_lst)->next != NULL)
		(*env_lst) = (*env_lst)->next;
	if ((*env_lst)->next == NULL)
	{
		(*env_lst)->next = (&(*node));
		(*node).prev = *env_lst;
		(*node).next = NULL; 
		env_lst = &temp;
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
