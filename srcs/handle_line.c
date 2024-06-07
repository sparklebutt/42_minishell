/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:17:55 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/07 15:22:06 by vkettune         ###   ########.fr       */
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
	tokens = data.tokens;
	i = -1;
	cmd = cmd_to_lower(tokens->args[0]);
	if (ft_strncmp(cmd, "exit", 5) == 0) // if exit command is given, exit the program
		return (ft_exit(cmd)); // leaks cause it dodes not free cmd
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(&data);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		ft_cd(&data, &envs, rl);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(rl);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(&data);
	else if(ft_strncmp(cmd, "export", 7) == 0)
		ft_export(&data);
	free(cmd);
	return (0);
}

int is_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 5) == 0) // only lowercase is valid
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0) // only lowercase is valid
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
	int i;

	i = -1;
	temp = NULL;
	if (ft_strncmp(cmd, "exit", 4) == 0)
		exit_true = 0;
	else
		exit_true = 1;
	if (ft_strncmp(cmd, "cd", 2) != 0)
	{
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

	i = 0;
	data.tokens = tokens;
	if (tokens->args[0] == NULL)
		return (0); // fixes segfault on pressing enter with nothing in array
	cmd = cmd_to_lower(tokens->args[0]);
	ft_printf("cmd: %s|\n", cmd); //remove
	if (is_builtins(cmd) == 1)
	{
		exec_builtins(data, envs, line); // add cmd as a parameter
	}
	else if (find_passage(&data, "PATH", 1) == -1)
	{
		// free(args);
		// free(tokens->args[0]);
		// free_array(tokens->args);
		ft_printf("%s\n", line);
	}
	// 	ft_printf("%s\n", line);
	// else if (exec_readdir() == 1)
	// {
	// 	find_passage(&envs, "PATH", tokens->args);
	// }
	// if (exec_builtins(data, envs, line) != 0)
	// 	;
	free(cmd);
	return (0);
}
