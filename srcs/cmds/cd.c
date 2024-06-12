/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:08:14 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/12 15:46:12 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cd(t_data *data, t_env *envs) // needs work
{
	char *temp;
	char *temp2;
	t_tokens *tokens;
	// t_env *temp_env;
	(void)envs;

	tokens = data->tokens;
	if (ft_strncmp(tokens->args[0], "cd", 3) == 0 && tokens->args[1] == NULL)
	{
		// ft_printf("test\n");
		find_passage(data, "HOME", 2);
		if (chdir(data->tmp->filename) == 0)
		{
			free(data->tmp->filename);
			data->path = getcwd(NULL, 0);
			// temp_env = fill_old_pwd(t_data *data, t_env *env, char *new_path)
			free(data->path);
		}
		return ;
	}
	// free(data->path); // not needed
	temp = getcwd(NULL, 0);
	// if (temp != NULL)
	// 	data->path = temp;
	if (ft_strncmp(tokens->args[1], "/", 1) != 0) // no '/' at the start of path
		data->path = ft_strjoin(temp, "/");
	free(temp);
	temp2 = ft_strdup(tokens->args[1]);
	// if (data->path != NULL)
	temp = ft_strjoin(data->path, temp2);
	ft_printf("temp: %s\n", temp);
	free(temp2);
	if (check_dir(temp) && chdir(temp) == 0) // add access check fucntion
	{
		ft_printf("path: %s\n", temp);
		// data->path = getcwd(NULL, 0); //remove
		envs = fill_pwd_and_oldpwd(data, envs, temp); // this is broken!!!!
		// free(data->path);
		// if (envs-value != NULL)
		// 	free(envs->value);
		// envs->value = fill_old_pwd(data, data->env, data->path);
		// free(temp);
		// return ;
	}
	else if (!check_dir(temp))
		cmd_error(tokens->args[0], tokens->args[1], "Permission denied");
	else
		cmd_error(tokens->args[0], tokens->args[1], "No such file or directory");
	free(temp);
	free(data->path);
}

int	check_dir(char *str)
{
	struct dirent		*dp;
	DIR							*test;

	test = NULL;
	if (access(str, X_OK) == 0)
		test = opendir(str);
	if (test == NULL)
		return (0);
	dp = readdir(test);
	if (dp == NULL)
	{
		closedir(test);
		return (0);
	}
	closedir(test);
	return (1);
}
