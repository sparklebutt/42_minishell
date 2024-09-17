/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:47:46 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/17 08:21:18 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*move_list(t_env *envs, char *key)
{
	t_env	*temp;

	temp = envs;
	while (temp->next != NULL) {
		if (ft_strnstr(temp->key, key, ft_strlen(temp->key) + 1) && ft_strlen(temp->key) == ft_strlen(key))
			break;
		temp = temp->next;
	}
	return (temp);
}

t_env	*replace_value(t_env *env, char *key, char *new_value)
{
	env = move_list(env, key);
	while (env != NULL) {
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0) {
			env->value = free_string(env->value);
			env->value = new_value;
			key = free_string(key);
			return (env);
		}
		env = env->next;
	}
	key = free_string(key);
	return (NULL);
}

int	insert_node(t_env **env_lst, char *key_name, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL) {
		free_nodes(*env_lst);
		return (-1);
	}
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

