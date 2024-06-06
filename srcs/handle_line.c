/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:17:55 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/06 18:25:44 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_builtins(t_data data, t_env envs, char *rl)
{
	char *temp;
	char *cmd;
	t_tokens *tokens;
	int i;
	
	temp = NULL;
	// temp2 = NULL;
	tokens = data.tokens;
	i = -1;
	cmd = cmd_to_lower(tokens->args[0]);
	// find_key_name(envs, "HOME");
	// ft_printf("next key: %s\n", .menvs.value);
	// ft_printf("home: %s\n", &temp2->key);
	// ft_printf("envs: %s\n", temp2);
	// rl = cmd_to_lower(rl);
	// ft_printf("fuck this\n");
	// ft_printf("cmd inside exec: %s|\n", cmd); //remove
	// ft_printf("final cmd: %s|\n", cmd); //remove
	if (ft_strncmp(cmd, "exit", 5) == 0) // if exit command is given, exit the program
		return (ft_exit(cmd)); // leaks cause it dodes not free cmd
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(&data);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		ft_cd(&data, &envs, rl);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
	{
		// ft_printf("echo\n");
		ft_echo(rl);	
	}
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(&data);
	else if(ft_strncmp(cmd, "export", 7) == 0)
		ft_export(&data);
	// else 
	// ft_printf("AAAAAAA %s\n", rl);
	// if (!tokens->args && tokens->args[0] == NULL)
	// 	ft_printf("CCCCCCC\n");
	// else 
	// 	ft_printf("BBBBBBB %s\n", tokens->args[0]);
	// else if (find_passage(&envs, "PATH", data.tokens) != 0)
	// 	ft_printf("%s\n", rl);
	return (0);
}

int is_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0) // only lowercase is valid
		return (1);
	return (0);
}

char *cmd_to_lower(char *cmd)
{
	char *temp;
	int exit_true;
//	char *cmd;
	int i;

	i = -1;
	temp = NULL;
	if (ft_strncmp(cmd, "exit", 4) == 0)
		exit_true = 0;
	else
		exit_true = 1;
	if (ft_strncmp(cmd, "cd", 2) != 0)
	{
		// ft_printf("rl: %s|\n", rl); //remove
		// cmd = ft_strchcpy(temp, rl, ' ');
		// ft_printf("after strchcpy cmd: %s|\n", cmd); //remove
		while (cmd && cmd[++i] != '\0')
			cmd[i] = ft_tolower(cmd[i]);
		// ft_printf("after tolower cmd: %s|\n", cmd); //remove
		// if (ft_strncmp(cmd, "echo", 5) == 0)
		// {
		// 	// ft_printf("added space\n"); //remove
		// 	// ft_printf("rl: %s|\n", rl); //remove
		// 	temp = ft_memmove(rl, cmd, 4);
		// 	// ft_printf("rl: %s|\n", rl); //remove
		// }
	}
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		cmd = ft_strdup("cd ");
	else 
		ft_printf("%s: command not found\n", cmd);
	if (exit_true == 0 && ft_strncmp(cmd, "exit", 5) == 0)
		ft_printf("exit\n");
	return (cmd);
}

int	handle_line(t_data data, t_env envs, t_tokens *tokens, char *line)
{
	int i;
	char *cmd;
	(void)envs;

	i = 0;
	data.tokens = tokens;
	// ft_printf("arg 0: %s|\n", tokens->args[0]); //remove
	// ft_printf("arg 1: %s|\n", tokens->args[1]); //remove
	// handle line to do:
		// check line (spaces, export, quotes, >, <, pipes, etc.)
		// parse line
		// call pipex & reset pipes / childen

	if (tokens->args[0] == NULL)
		return (0); // fixes segfault on pressing enter with nothing in array
	cmd = cmd_to_lower(tokens->args[0]);
	ft_printf("cmd: %s|\n", cmd); //remove
	if (is_builtins(cmd) == 1)
	{
		// free_string(cmd); // fixes leaks but stops pwd from working
		exec_builtins(data, envs, line);
	}
	else
	{
		find_passage(&data, "PATH", 1);
		ft_printf("%s\n", line);
	}
	// 	ft_printf("%s\n", line);
	// else if (exec_readdir() == 1)
	// {
	// 	find_passage(&envs, "PATH", tokens->args);
	// }
	// if (exec_builtins(data, envs, line) != 0)
	// 	;
	return (0);
}
