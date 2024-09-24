/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:56:54 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/24 17:45:32 by vkettune         ###   ########.fr       */
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

void	loop_args_in_unset(t_env **env, char *key_name)
{
	t_env	*current_env;
	t_env	*prev_env;
	int		len;

	current_env = *env;
	prev_env = NULL;
	len = ft_strlen(key_name);
	if (current_env != NULL && ft_strncmp(current_env->key, key_name, len) == 0)
	{	
		*env = current_env->next;
		free_node(current_env);
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

void	ft_unset(t_env **env, char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL && args[i][0] != '|' && is_redirect(args[i]) == 0)
	{
		loop_args_in_unset(env, args[i]);
		i++;
	}
}
