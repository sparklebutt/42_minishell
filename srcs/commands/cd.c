/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:08:14 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/08 15:20:21 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cd(t_data *data, t_env *envs)//, t_tokens *tokens)
{
	char *path;
	char *temp2;
	t_tokens *tokens;
	(void)envs;

	tokens = data->tokens;
	ft_printf("old data->path: %s\n", data->path);
	if (ft_strncmp(tokens->args[0], "cd", 3) == 0 && tokens->args[1] == NULL)
	{
		find_passage(data, "HOME", 2);
		if (chdir(data->tmp->filename) == 0)
		{
			free(data->tmp->filename);
			free(data->path);
			data->path = getcwd(NULL, 0);
		}
		return ;
	}
	free(tokens->args[0]); // idk how this fixes leaks
	path = getcwd(NULL, 0);
	if (path != NULL)
		data->path = path;
	if (ft_strchr(tokens->args[1], '$') == 0)
	{
		//key = find_key(tokens->args[1]);
		find_key_from_envs(data, tokens->args[1]);
	}
	if (ft_strncmp(tokens->args[1], "/", 1) != 0)
	{
		ft_printf("no / at the start of path\n"); //remove
		temp2 = ft_strjoin("/", tokens->args[1]);
		ft_printf("temp2: %s\n", temp2); //remove
	}
	else
	{
		ft_printf("slash in path\n"); //remove
		temp2 = ft_strdup(tokens->args[1]);
		ft_printf("temp2: %s\n", temp2); //remove
	}
	free(tokens->args[1]); // idk how this fixes leaks
	free(data->path); // idk how this fixes leaks, and actually works
	path = ft_strjoin(data->path, temp2);
	free(temp2);
	ft_printf("path: %s\n", path); //remove
	if (chdir(path) == 0)
	{
		data->path = getcwd(NULL, 0);
	}
	else
	{
		ft_printf("error\n"); // what error?? we need "return (cmd_error(cmd, msg));"" function
	}
	free(path);
	ft_printf("new pwd: %s\n", data->path); //remove
	free(data->path);
}