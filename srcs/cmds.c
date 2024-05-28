/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:28:04 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/28 19:01:02 by araveala         ###   ########.fr       */
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
	{
		// free(data->path);
		data->path = temp;
	}
	ft_printf("%s\n", data->path);
	return (0);
}

void ft_cd(t_data *data, t_env *envs, char *rl)
{
	char *temp;
	char *temp2;
	t_tokens *tokens;
	(void)envs;

	
	tokens = data->tokens;
	if (ft_strncmp(rl, "cd", 3) == 0)
	{
		// ft_printf("return to HOME: connect this with env (alexandra)\n");
		find_passage(data, "HOME", 2);
		printf("our path that should be checked by the open and read dir = %s\n", data->tmp->filename);
		chdir(data->tmp->filename);
//		free_string(data->tmp->filename);// when done with confirmed path?
		return ;
	}
	temp = getcwd(NULL, 0);
	if (temp == NULL)
		free(temp);
	else
	{
		// ft_printf("temp: %s\n", data->path);
		// free(data->path);
		data->path = temp;
	}
	ft_printf("old pwd: %s\n", data->path); //remove
	// free(data->path);
	temp = ft_strtrim(rl, "cd ");
	temp2 = ft_strjoin("/", temp);
	free(temp);
	temp = ft_strjoin(data->path, temp2);
	free(temp2);
	chdir(temp);
	if (chdir(temp) == 0)
	{
		free(data->path);
		data->path = getcwd(NULL, 0);
	}
	else
	{
		ft_printf("error\n");
		error(tokens->args[0], strerror(errno)); 
	}
	// free(temp);
	// data->path = getcwd(NULL, 0);
	ft_printf("new pwd: %s\n", data->path); //remove
}

void ft_echo(char *rl)
{
	char *temp;
	// int i;

	ft_printf("before trim: '%s'\n", rl);
	temp = trim_start(rl);
	ft_printf("after trim: '%s'\n", temp);
	// i = 0;
	// while (args[i++] != '|' || args[i] != NULL)
	// {
	// 	temp = ft_strjoin(args[i], " ");
	// }
	handle_quotes(&temp);
	ft_printf("after handling quotes: '%s'\n", temp);
	ft_printf("%s\n", temp);
}

char	*trim_start(char *str)
{
	int i;
	int j;
	char *c;

	i = 0;
	j = 0;
	c = "echo  ";
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
	// ft_printf("before handling quotes temp: %s\n", temp);
	while (temp[i] != '\0')
	{
		// \" means the string is inside quotes
		if (temp[i] == '\"')
		{
			temp2 = ft_strtrim(temp, "\"");
			temp = temp2;
			free(temp2); // maybe
			break;
		}
		i++;
	}
	// ft_printf("after temp: %s\n", temp);
	*str = temp;
}

int ft_exit(char *cmd)
{
	// (void)cmd;
	free(cmd);
	ft_printf("exit\n");
	exit(0);
	return (1);
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
