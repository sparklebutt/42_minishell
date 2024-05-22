/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:28:04 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/22 14:15:14 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_data *data)
{
	if (!(getcwd(NULL, 0) == NULL))
		data->path = getcwd(NULL, 0);
	ft_printf("%s\n", data->path);
	return (0);
}

char *ft_cd(t_data *data, char *rl)
{
	char *temp;
	char *temp2;

	temp = NULL;
	temp2 = NULL;
	if (!(getcwd(NULL, 0) == NULL))
		data->path = getcwd(NULL, 0);
	if (ft_strncmp(rl, "cd", 3) == 0)
	{
		
		chdir(HOME);
	}
	ft_printf("old pwd: %s\n", data->path); // remove
	free(data->path); // remove
	temp = ft_strtrim(rl, "cd ");
	temp2 = ft_strjoin("/", temp);
	free(temp);
	temp = ft_strjoin(data->path, temp2);
	free(temp2);
	chdir(temp);
	free(temp);
	data->path = getcwd(NULL, 0);
	ft_printf("new pwd: %s\n", data->path); // remove
	return (data->path);
}
