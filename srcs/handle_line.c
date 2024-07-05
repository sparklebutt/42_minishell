/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:17:55 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/05 11:34:44 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_builtins(t_data data, t_env envs, char *rl, char *cmd)
{
	t_tokens *tokens;
	
	tokens = data.tokens;
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

//static int	check_for_cmd()
//{

//}

int	handle_pipe_line(t_data data, t_env envs, t_tokens *tokens, char *line)
{
	char *cmd;
	int	pipes;
	int i;

	i = 0;
	pipes = tokens->pipe_count * 2;
	data.tokens = tokens;
	if (tokens->args[0] == NULL)
		return (0);
	while (tokens->args[i] && pipes > 0)
	{
		cmd = tokens->args[i];
		ft_printf("cmd = %s\n", cmd);
		if (is_builtins(cmd) == 1)
		{

			exec_builtins(data, envs, line, cmd);
		}
		else
		{
			if (find_passage(&data, cmd, "PATH", 1) == -1)
				call_cmd_error(cmd, NULL, "command not found\n", -10);
		}
		i++;
		pipes--;
	}
//	free(cmd);
	return (0);
}

int	handle_line(t_data data, t_env envs, t_tokens *tokens, char *line)
{
	char *cmd;

	data.tokens = tokens;
	if (tokens->args[0] == NULL)
		return (0);
	cmd = tokens->args[0];
	if (is_builtins(cmd) == 1)
	{

		exec_builtins(data, envs, line, cmd);
	}
	else if (find_passage(&data, cmd, "PATH", 1) == -1)
		call_cmd_error(cmd, NULL, "command not found\n", -10);
	free(cmd);
	return (0);
}

/*int	handle_line(t_data data, t_env envs, t_tokens *tokens, char *line)
{
	char *cmd;

	data.tokens = tokens;
	if (tokens->args[0] == NULL)
		return (0);
	cmd = tokens->args[0];
//	printf("heywo\n");
	if (is_builtins(cmd) == 1)
	{

		exec_builtins(data, envs, line, cmd);
	}
	else if (find_passage(&data, cmd, "PATH", 1) == -1)
		call_cmd_error(cmd, NULL, "command not found\n", -10);
	free(cmd);
	return (0);
}*/
