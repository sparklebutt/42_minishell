/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:08:14 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/13 14:38:45 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_home(t_data *data, t_env *envs)
{
	find_passage(data, "HOME", 2);
	if (chdir(data->tmp->filename) == 0)
	{
		envs = move_list(envs, "PWD");
		envs = fill_old_pwd(data, envs, data->tmp->filename);
	}
}

void	change_dir(t_data *data, t_env *envs, char *temp)
{
	t_tokens	*tokens;

	tokens = data->tokens;
	if (check_dir(temp) && chdir(temp) == 0)
	{
		envs = move_list(envs, "PWD");
		envs = fill_old_pwd(data, envs, temp);
	}
	else if (!check_dir(temp))
		cmd_error(tokens->args[0], tokens->args[1]);
	else
		cmd_error(tokens->args[0], tokens->args[1]);
}

void	ft_cd(t_data *data, t_env *envs)
{
	char	*temp;
	char	*temp2;

	if (ft_strncmp(data->tokens->args[0], "cd", 3) == 0
		&& data->tokens->args[1] == NULL)
	{
		to_home(data, envs);
		return ;
	}
	temp = getcwd(NULL, 0);
	if (temp != NULL) // add same error handling than what pwd has
		data->path = temp;
	if (ft_strncmp(data->tokens->args[1], "/", 1) != 0)
		data->path = ft_strjoin(temp, "/");
	free(temp);
	temp2 = ft_strdup(data->tokens->args[1]);
	temp = ft_strjoin(data->path, temp2);
	free(temp2);

	change_dir(data, envs, temp);
	free(data->path);
}

int	check_dir(char *str)
{
	struct dirent		*dp;
	DIR					*test;

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
