/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:17:55 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/01 17:44:29 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_builtins(t_data data, t_env envs, char *rl, char *cmd)
{
	// char *temp;
	t_tokens *tokens;
	// int i;
	
	// temp = NULL;
	tokens = data.tokens;
	// i = -1;
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (ft_exit(cmd, tokens));
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(&data, &envs);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		ft_cd(&data, &envs);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(rl);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(&data);
	else if(ft_strncmp(cmd, "export", 7) == 0)
		ft_export(&data);
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
	// char *temp;
	int i;

	i = -1;
	// temp = NULL;
	if (ft_strncmp(cmd, "cd", 2) != 0)
	{
		while (cmd && cmd[++i] != '\0')
			cmd[i] = ft_tolower(cmd[i]);
	}
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (ft_strdup(cmd));
	else 
		ft_printf("%s: command not found\n", cmd);
	return (ft_strdup(cmd));
}

int	handle_line(t_data data, t_env envs, t_tokens *tokens, char *line)
{
	// int i;
	char *cmd;

	// i = 0;
	data.tokens = tokens;
	if (tokens->args[0] == NULL)
		return (0);
	cmd = cmd_to_lower(tokens->args[0]);
	// ft_printf("cmd: %s|\n", cmd); //remove
	if (is_builtins(cmd) == 1)
		exec_builtins(data, envs, line, cmd);
	else if (find_passage(&data, cmd, "PATH", 1) == -1)
		call_cmd_error(cmd, NULL, "command not found\n", -10);
	free(cmd);
	return (0);
}
