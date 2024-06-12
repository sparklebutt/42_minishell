/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:05:46 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/12 18:00:07 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_data *data)
{
	t_env *env;
	char *temp_path;

	env = data->env;
	temp_path = getcwd(NULL, 0);
	if (temp_path != NULL)
	{
		free(data->path);
		data->path = temp_path;
	}
	else if (temp_path == NULL)
	{
		if (find_key("OLDPWD") != NULL)
		{
			env = move_list(env, "OLDPWD");
			if (env->value != NULL)
				data->path = ft_strdup(env->value);
		}
		else
		{
			cmd_error("pwd", "OLDPWD", "not found");
			return (-1);
		}
	}
	ft_printf("%s\n", data->path);
	free(temp_path);
	return (0);
}

t_env *fill_old_pwd(t_data *data, t_env *env, char *new_path) // needs fixing
{
	char *temp;

	new_path = getcwd(NULL, 0);
	temp = NULL;
	if (find_node(env, "PWD", data) == 1)
	{
		env = move_list(env, "PWD");
		temp = ft_strdup(env->value);
		// ft_printf("temp = %s\n", temp);
		// ft_printf("env line = %s\n", data->tmp->env_line); find node stores an env line that is usable each find node, must also free it,
		free_string(data->tmp->env_line);
	}
	else
	{
		cmd_error("cd", "PWD", "not found");
		return (NULL);
	}
	if (find_node(env, "OLDPWD", data) == 1)
	{
		env = move_list(env, "OLDPWD");
		if (env->value != NULL)
			free(env->value);
		env->value = ft_strdup(temp);
		free(temp);
		free_string(data->tmp->env_line);
	}
	else
	{
		cmd_error("cd", "OLDPWD", "not found");
		return (NULL);
	}
	env = move_list(env, "PWD");
	if (env->value != NULL)
		free(env->value);
	ft_printf("new_path: %s\n", new_path);
	env->value = ft_strdup(new_path);
	free(new_path);
	return (env);
}


// char *fill_old_pwd(t_data *data, t_env *env, char *new_path) // needs testing
// {
// 	char *temp;

// 	new_path = getcwd(NULL, 0);
// 	temp = NULL;
// 	if (find_node(env, "PWD", data) == 1)
// 	{
// 		env = move_list(env, "PWD");
// 		temp = ft_strdup(env->value);
// 	}
// 	else
// 	{
// 		cmd_error("cd", "PWD", "not found");
// 		return (NULL);
// 	}
// 	if (find_node(env, "OLDPWD", data) == 1)
// 	{
// 		env = move_list(env, "OLDPWD");
// 		if (env->value != NULL)
// 			free(env->value);
// 		env->value = ft_strdup(temp);
// 	}
// 	else
// 	{
// 		cmd_error("cd", "OLDPWD", "not found");
// 		return (NULL);
// 	}
// 	env = move_list(env, "PWD");
// 	if (env->value != NULL)
// 		free(env->value);
// 	env->value = ft_strdup(new_path);
// 	free(temp);
// 	free(new_path);
// 	return (env->value);
// }
