/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:17:55 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/08 16:05:16 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_data data, char *cmd, int fd, int r_w)
{
	t_env		envs;		
	t_tokens	*tokens;

	if (fd == 9 || r_w == 9)
		printf("holding incase we need these parameters"); // might not be needed, delete this
	envs = *data.env;
	tokens = data.tokens;
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (ft_exit(cmd, tokens));
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(&data, &envs);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		ft_cd(&data, &envs);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(tokens->args);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(&data);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ft_export(&data);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ft_unset(&envs, tokens->args[1]);
	return (0);
}

int	is_builtins(char *cmd)
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
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

int	handle_line(t_data data, t_tokens *tokens)
{
	data.tokens = tokens;
	if (tokens->args[0] == NULL)
		return (0);
	if (tokens->args[data.i] != NULL)
	{
		if (tokens->pipe_count == 0 && is_builtins(tokens->args[data.i]) == 1)
			exec_builtins(data, tokens->args[data.i], 0, 0);
		else if (find_passage(&data, "PATH", 1) == -1)
			call_cmd_error(tokens->args[data.i], NULL, "command not found\n", -10);
		data.i++;
	}
	return (0);
}
