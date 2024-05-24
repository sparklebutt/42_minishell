/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:12:21 by araveala          #+#    #+#             */
/*   Updated: 2024/05/22 16:57:07 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *add_new_node(char *value_in, char *key_in)
{
	t_env *new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
	{
		printf("new node creation failure\n");
		return (0);
	}
	new->next = NULL;
	new->value = value_in;
	new->key  = key_in;
	new->prev = NULL;
	return (new);
}

void addnode(t_env **env_lst, t_env *node) //to end
{
	t_env *temp;

	temp = (*env_lst);
	while ((*env_lst)->next != NULL)
		(*env_lst) = (*env_lst)->next;
	if ((*env_lst)->next == NULL)
	{
		(*env_lst)->next = (&(*node));
		(*node).prev = *env_lst;
		(*node).next = NULL; 
		env_lst = &temp; //return pointer 
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
