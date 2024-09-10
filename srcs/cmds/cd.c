/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:08:14 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/10 14:16:06 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_home(t_data *data, t_env *envs)
{
	find_passage(data, "HOME", 2);
	if (chdir(data->tmp->env_line) == 0)
		envs = fill_old_pwd(data, envs, data->tmp->env_line);
}

void	change_dir(t_data *data, t_env *envs, char *temp)
{
	t_tokens	*tokens;
	char *temp2;

	temp2 = NULL;
	tokens = data->tokens;
	free_string(data->path);
	if (check_dir(temp) && chdir(temp) == 0 && find_node(envs, "OLDPWD", data) == 1 && find_node(envs, "PWD", data) == 1)
	{
		temp2 = getcwd(NULL, 0);
		envs = fill_old_pwd(data, envs, temp2);
	}
	else if (find_node(envs, "OLDPWD", data) == 0 || find_node(envs, "PWD", data) == 0)
		return ;
	else
		cmd_error(tokens->args[data->i], tokens->args[data->i + 1]);
	free_string(temp2);
	free_string(temp);
}

void	ft_cd(t_data *data, t_env *envs)
{
	char	*temp;
	char	*temp2;
	int		i;
	
	i = data->i;
	if (ft_strncmp(data->tokens->args[i], "cd", 3) == 0
		&& data->tokens->args[i + 1] == NULL)
	{
		to_home(data, envs);
		return ;
	}
	temp = getcwd(NULL, 0);
	if (temp != NULL)
		free_string(data->path);
	if (temp != NULL)
		data->path = ft_strdup(temp);
	if (ft_strncmp(data->tokens->args[i + 1], "/", 1) != 0)
		free_string(data->path);	
	if (ft_strncmp(data->tokens->args[i + 1], "/", 1) != 0)
		data->path = ft_strjoin(temp, "/");
	free_string(temp);
	temp2 = ft_strdup(data->tokens->args[++i]);
	temp = ft_strjoin(data->path, temp2);
	free_string(temp2);
	change_dir(data, envs, temp);
}

int	check_file(char *str)
{
	if (access(str, X_OK) == -1)
	{
		printf("access failed for string = %s\n", str);
		return(1);
	}
	return (0);	
}

int	check_dir(char *str)
{
	struct dirent		*dp;
	DIR					*test;

	test = NULL;
	
	if (access(str, X_OK) == -1)
	{
		printf("\t\taccess failed for string ceck dir= %s\n", str);
		return(0);
	}
	else
		test = opendir(str);
	if (test == NULL)
	{
		printf("open opened null\n");
		return (0);
	}
	dp = readdir(test);
	if (dp == NULL)
	{
		printf("read failed = null\n");
		closedir(test);
		return (0);
	}
	closedir(test);
	return (1);
}
