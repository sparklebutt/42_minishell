/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:05:46 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/12 15:49:53 by vkettune         ###   ########.fr       */
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

t_env *fill_pwd_and_oldpwd(t_data *data, t_env *env, char *new_pwd) // needs fixing
{
	char *new_oldpwd;

	// new_pwd = getcwd(NULL, 0);
	// new_oldpwd = NULL;
	if (find_node(env, "PWD", data) == 1)
	{
		env = move_list(env, "PWD");
		if (env->value != NULL)
			new_oldpwd = ft_strdup(env->value);
		env = replace_value(env, ft_strdup("PWD"), new_pwd);
	}
	else
	{
		cmd_error("cd", "PWD", "not found");
		return (NULL);
	}
	if (find_node(env, "OLDPWD", data) == 1)
	{
		ft_printf("oldpwd found\n");
		env = move_list(env, "OLDPWD");
		if (env->value != NULL)
			free(env->value);
		env->value = new_oldpwd;
	}
	else
	{
		cmd_error("cd", "OLDPWD", "not found");
		return (NULL);
	}
	env = move_list(env, "PWD");
	if (env->value != NULL)
		free(env->value);
	ft_printf("new_path: %s\n", new_pwd);
	env->value = ft_strdup(new_pwd);
	free(new_pwd);
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
