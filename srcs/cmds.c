/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:28:04 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/24 11:12:11 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_data *data)
{
	char *temp;
	// char *trash_dir;

	// ft_printf("%s\n", data->path);
	// trash_dir = "$HOME/.Trash"; // a guess, probably doesn't work
	temp = getcwd(NULL, 0);
	// if (temp == NULL || ft_strncmp(temp, trash_dir, ft_strlen(trash_dir) + 1) == 0)
	if (temp == NULL) //remove
		free(temp);
	else
		data->path = temp;
	ft_printf("%s\n", data->path);
	return (0);
}

void ft_cd(t_data *data, char *rl)
{
	char *temp;
	char *temp2;

	if (ft_strncmp(rl, "cd", 3) == 0)
	{
		ft_printf("return to HOME: connect this with env (alexandra)\n");
		return ;
	}
	temp = getcwd(NULL, 0);
	if (temp == NULL)
		free(temp);
	else
		data->path = temp;
	// ft_printf("old pwd: %s\n", data->path); //remove
	free(data->path);
	temp = ft_strtrim(rl, "cd ");
	temp2 = ft_strjoin("/", temp);
	free(temp);
	temp = ft_strjoin(data->path, temp2);
	free(temp2);
	chdir(temp);
	free(temp);
	data->path = getcwd(NULL, 0);
	// ft_printf("new pwd: %s\n", data->path); //remove
}

void ft_echo(char *rl)
{
	char *temp;

	// ft_printf("before trim: '%s'\n", rl);
	temp = trim_start(rl);
	// ft_printf("after trim: '%s'\n", temp);
	handle_quotes(&temp);
	// ft_printf("after handling quotes: '%s'\n", temp);
	ft_printf("%s\n", temp);
}

char	*trim_start(char *str)
{
	int i;
	int j;
	char *c;

	i = 0;
	j = 0;
	c = "echo";
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] == c[j] && c[j] != '\0')
	{
		i++;
		j++;
	}
	return (str + i);
}

void handle_quotes(char **str)
{
	char *temp;
	char *temp2;
	int i;

	i = 0;
	temp = *str;
	while (temp[i] != '\0')
	{
		// \" means the string is inside quotes
		if (temp[i] == '\"')
		{
			temp2 = ft_strtrim(temp, "\"");
			free(temp);
			temp = temp2;
			break;
		}
		i++;
	}
	*str = temp;
}

int ft_exit(char *cmd)
{
	free(cmd);
	ft_printf("exit\n");
	return (-1);
}

void ft_env(char *rl, char *cmd, t_env envs)
{
	(void)cmd;
	(void)rl;
	// make so that "Env ghjk" does not work and throws an error
	// ft_strtrim(rl, "env ");
	// if (ft_strncmp(rl, "env", 3) != 0)
	// {
	// 	ft_printf("env: command not found\n");
	// 	return ;
	// }
	while (envs.next != NULL)
	{
		printf("%s\n", envs.value);
		envs = *envs.next;
	}
}