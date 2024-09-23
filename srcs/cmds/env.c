/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:28 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/23 17:47:23 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *close_n_return(DIR *dir)
{
	closedir(dir);
	return ("env");
}


char *loop_path(t_data *data)
{
	DIR				*dir;
	struct dirent	*dp;
	int				i;

	i = 0;
	while (data->tmp->array && data->tmp->array[i])
	{
		if (data->tmp->array && check_dir(data->tmp->array[i]) == 1)
		{
			dir = opendir(data->tmp->array[i]);
			dp = readdir(dir);
			while (dp != NULL)
			{
				if (ft_strncmp(dp->d_name, "env", 3) == 0
					&& ft_strlen(dp->d_name) == 3)
					return (close_n_return(dir));
				if (i != 0)
					dp = readdir(dir);
			}
			closedir(dir);
		}
		i++;
	}
	return (NULL);
}

char	*env_helper(t_data *data, t_env *env)
{
	char	*value;
	char	*ret;

	ret = NULL;
	value = find_keys_value(env, "PATH");
	if (value == NULL || ft_strlen(value) == 0)
		return (NULL);
	data->tmp->array = ft_split(value, ':');
	if (data->tmp->array == NULL)
		not_perror("path array", NULL, "malloc failn");
	ret = loop_path(data);
	return (ret);
}

void	ft_env(t_env **envs, t_data *data)
{
	t_env	*temp_env;
	char	*ret;

	ret = NULL;
	temp_env = *envs;
	// printf("check\n");
	if (find_node(*envs, "PATH", data) == 1)
	{
		// printf("found PATH with something in it from env\n");
		ret = env_helper(data, *envs);
		if (ret == NULL)
			return (not_perror("env", NULL, "No such file or directory\n"));
	}
	else
		return (not_perror("env", NULL, "No such file or directory\n"));
	// printf("what  is ret? %s\n", ret);
	free_array(data->tmp->array);
	if (data->tokens->args[data->i + 1] != NULL
		&& data->tokens->args[data->i + 1][0] != '|'
		&& is_redirect(data->tokens->args[data->i + 1]) > 0)
			return (cmd_error("env", data->tokens->args[data->i + 1]));
	while (temp_env != NULL)
	{
		printf("%s=%s\n", temp_env->key, temp_env->value);
		temp_env = temp_env->next;
	}
}
