/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:05:46 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/10 14:01:33 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data, t_env *envs)
{
	char	*temp_path;

	temp_path = getcwd(NULL, 0);
	if (temp_path != NULL)
	{
		free_string(data->path);
		data->path = temp_path;
	}
	else if (temp_path == NULL)
	{
		if (find_key("OLDPWD") != NULL)
		{
			envs = move_list(envs, "OLDPWD");
			if (envs->value != NULL)
				data->path = ft_strdup(envs->value);
			else
				return (call_cmd_error("pwd", "OLDPWD", NULL, -1));
		}
		else
			return (call_cmd_error("pwd", "OLDPWD", NULL, -1));
	}
	ft_printf("%s\n", data->path);
	free_string(temp_path);
	return (0);
}

t_env	*update_oldpwd(t_data *data, t_env *env, char *temp)
{
	t_env	*temp_env;

	temp_env = data->env;	
	env = move_list(temp_env, "OLDPWD");
	if (env->value != NULL)
		free_string(env->value);
	env->value = ft_strdup(temp);
	return (env);
}

t_env	*fill_old_pwd(t_data *data, t_env *env, char *new_path)
{
	t_env	*temp_env;
	char	*temp;

	temp = NULL;
	temp_env = env;
	if (find_node(temp_env, "PWD", data) == 1)
		temp = data->tmp->env_line;
	else
		return (call_env_error("cd", "PWD"));
	if (find_node(env, "OLDPWD", data) == 1)
		env = update_oldpwd(data, env, temp);
	else
		return (call_env_error("cd", "OLDPWD"));
	env = move_list(temp_env, "PWD");
	if (env->value != NULL)
		free_string(env->value);
	env->value = ft_strdup(new_path);
	return (env);
}
