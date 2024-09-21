/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:08:14 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 12:51:19 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(t_data *data, t_env *envs, char *temp)
{
	t_tokens	*tokens;
	char		*temp2;

	temp2 = NULL;
	tokens = data->tokens;
	data->path = free_string(data->path);
	if (check_dir(temp) && chdir(temp) == 0
		&& find_node(envs, "OLDPWD", data) == 1
		&& find_node(envs, "PWD", data) == 1)
	{
		if (find_node(envs, "PWD", data) > 0)
			temp2 = getcwd(NULL, 0);
		if (find_node(envs, "OLDPWD", data) > 0)
			envs = fill_old_pwd(data, envs, temp2);
	}
	else
		cmd_error(tokens->args[data->i], tokens->args[data->i + 1]);
	temp2 = free_string(temp2);
	temp = free_string(temp);
}

int	is_slash(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] == '/')
		i++;
	if (ft_strlen(str) == i)
		return (1);
	return (0);
}

void	handle_cd_input(t_data *data, t_env *envs, int i, char *temp)
{
	char	*temp2;

	if (ft_strncmp(data->tokens->args[i + 1], "/", 1) != 0)
	{
		data->path = free_string(data->path);
		data->path = ft_strjoin(temp, "/");
	}
	temp = free_string(temp);
	temp2 = ft_strdup(data->tokens->args[++i]);
	change_dir(data, envs, temp2);
}

void	to_home(t_data *data, t_env *envs)
{
	find_passage(data, "HOME", 2);
	if (chdir(data->tmp->env_line) == 0)
		envs = fill_old_pwd(data, envs, data->tmp->env_line);
}

void	ft_cd(t_data *data, t_env *envs)
{
	char	*temp;
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
	{
		data->path = free_string(data->path);
		data->path = ft_strdup(temp);
	}
	else
	{
		printf("minishell: cd: cwd is null, go home, you're drunk\n");
		to_home(data, envs);
		return ;
	}
	handle_cd_input(data, envs, i, temp);
}
