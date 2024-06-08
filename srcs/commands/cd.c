/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:08:14 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/08 19:14:11 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cd(t_data *data, t_env *envs)
{
	char *temp;
	char *temp2;
	t_tokens *tokens;
	(void)envs;

	tokens = data->tokens;
	if (ft_strncmp(tokens->args[0], "cd", 3) == 0 && tokens->args[1] == NULL)
	{
		find_passage(data, "HOME", 2);
		if (chdir(data->tmp->filename) == 0)
		{
			ft_printf("chdir success\n"); // remove
			free(data->tmp->filename);
			data->path = getcwd(NULL, 0);
			free(data->path);
		}
		return ;
	}
	free(data->path);
	temp = getcwd(NULL, 0);
	if (temp != NULL)
		data->path = temp;
	if (ft_strncmp(tokens->args[1], "/", 1) != 0)
	{
		// ft_printf("no / at the start of path\n"); //remove
		temp2 = ft_strjoin("/", tokens->args[1]);
	}
	else
	{
		// ft_printf("slash in path\n"); //remove
		temp2 = ft_strdup(tokens->args[1]);
	}
	ft_printf("temp2: %s\n", temp2); //remove
	// free(data->path);
	temp = ft_strjoin(data->path, temp2);
	free(temp2);
	if (chdir(temp) == 0)
		data->path = getcwd(NULL, 0);
	else
	{
		cmd_error(tokens->args[0], tokens->args[1], "No such file or directory");
		free(temp);
		return ;
	}
	free(temp);
	// ft_printf("new pwd: %s\n", data->path); //remove
	free(data->path);
}

