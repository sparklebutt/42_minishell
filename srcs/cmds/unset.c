/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:56:54 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/18 20:51:32 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_env *env)
{
	if (env != NULL)
	{
		env->key = free_string(env->key);
		env->value = free_string(env->value);
		free(env);
		env = NULL;
	}
}

void	ft_unset(t_env **env, char *key_name)
{
	t_env	*current_env;
	t_env	*prev_env;
	int		len;
	
	current_env = *env;
	prev_env = NULL;
	len = ft_strlen(key_name);
	if (current_env != NULL && ft_strncmp(current_env->key, key_name, len) == 0)
	{	
		// if (prev_env == NULL)
		// 	*env = current_env->next;
			//data->env = data->env->next;
			// printf("data->env->key 0 = %s\n", data->env->key);
			*env = current_env->next;
			// printf("data->env->key 1 = %s\n", data->env->key);
			// printf("data->env->next->key 1 = %s\n", data->env->next->key);
			free_node(current_env);
			// printf("data->env->key 2 = %s\n", data->env->key);
			// data->env = *env;
			// printf("data->env->key 3 = %s\n", data->env->key);
			return ;
	}
	while (current_env != NULL
		&& ft_strncmp(current_env->key, key_name, len) != 0)
	{
		prev_env = current_env;
		current_env = current_env->next;
	}
	if (current_env == NULL)
		return ;
	prev_env->next = current_env->next;
	free_node(current_env);
}
