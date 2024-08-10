/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:47:46 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/10 06:12:57 by vkettune         ###   ########.fr       */
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
	// printf("1 bbb\n");
	env = move_list(env, key);
	// printf("2 bbb\n");
	while (env != NULL) {
		// printf("3 bbb\n");
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0) {
			// printf("does it get here?\n");
			free(env->value);
			env->value = new_value;
			free(key);
			// printf("I LOVE CATS\n");
			return (env);
		}
		env = env->next;
	}
	free(key);
	// printf("meep\n");
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
	if (*env_lst == NULL) {
		*env_lst = new_node;
		return (1);
	}
	tmp = *env_lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	return (1);
}
