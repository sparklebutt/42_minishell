/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:05:46 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 12:49:46 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_is_null(t_data *data, t_env *envs, int check)
{
	if (check != 0)
	{
		envs = move_list(envs, "OLDPWD");
		data->path = ft_strdup(envs->value);
	}
	else
		return (-1); // exit code maybe
	return (0);
}

int	ft_pwd(t_data *data, t_env *envs)
{
	char	*temp_path;
	int		check;

	check = find_node(envs, "OLDPWD", data);
	temp_path = getcwd(NULL, 0);
	if (temp_path != NULL)
	{
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
