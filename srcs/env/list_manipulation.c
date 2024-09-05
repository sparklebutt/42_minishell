/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:47:46 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/20 17:25:18 by araveala         ###   ########.fr       */
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
/*int	set_direction(t_data *data)
{
	
	return (0); // no direction i guess
}*/
/*~~ new for redirs~~*/
/*int	insert_node_re(t_re **redir, char *direction, char *file)
{
	t_re	*new_node;
	t_re	*tmp;

	new_node = malloc(sizeof(t_re));
	if (new_node == NULL) {
		free_nodes(*redir);
		return (-1);
	}
	new_node->direction = direction;
	new_node->file = file;
	new_node->fd = 0;
	new_node->next = NULL;
	if (*redir == NULL) {
		*redir = new_node;
		return (1);
	}
	tmp = *redir;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	return (1);
}*/
