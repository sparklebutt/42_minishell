/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:05:46 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/18 08:21:48 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_is_null(t_data *data, t_env *envs, char *check)
{
	if (check != NULL)
	{
		check = free_string(check);
		envs = move_list(envs, "OLDPWD");
		if (envs->value != NULL)
			data->path = ft_strdup(envs->value);
		else
			return (call_cmd_error("pwd", "OLDPWD", NULL, -1));
	}
	else
		return (call_cmd_error("pwd", "OLDPWD", NULL, -1));
	return (0);
}

int	ft_pwd(t_data *data, t_env *envs)
{
	char	*temp_path;
	char	*check;

	check = find_key("OLDPWD");
	temp_path = getcwd(NULL, 0);
	if (temp_path != NULL)
	{
		check = free_string(check);
		data->path = free_string(data->path);
		data->path = temp_path;
	}
	else if (temp_path == NULL)
	{
		if (path_is_null(data, envs, check) == 1)
			return (1);
	}
	ft_printf("%s\n", data->path);
	temp_path = free_string(temp_path);
	return (0);
}

t_env	*update_oldpwd(t_data *data, t_env *env, char *temp)
{
	t_env	*temp_env;

	temp_env = data->env;
	env = move_list(temp_env, "OLDPWD");
	if (env->value != NULL)
		env->value = free_string(env->value);
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
		env->value = free_string(env->value);
	env->value = ft_strdup(new_path);
	return (env);
}
