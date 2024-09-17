/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:17:55 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/17 14:43:54 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_data data, char *cmd)
{
	t_env		envs;		
	t_tokens	*tokens;

	// printf("cmd =  %s\n", cmd);
	envs = *data.env;
	tokens = data.tokens;
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (ft_exit(&data, cmd, tokens));
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		ft_cd(&data, &envs);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(&data, &envs);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ft_export(&data);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ft_unset(&envs, tokens->args[1]);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(&data, tokens->args);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(&data);
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
		// MARK
		//printf("redir count = %d\n", tokens->redirect_count);
		// printf("\t\texit code = %d\n", exit_code(0, 0)); // just want to retrieve it
		/*if (data.i == 0 && tokens->args[data.i][0] == '<')
		{
			data.i++;
			if (tokens->args[data.i][1] == '<')
			data.i ++;
		}*/
		if (tokens->pipe_count == 0 && tokens->redirect_count == 0 && is_builtins(tokens->args[data.i]) == 1)
		{
			// printf("stepping into exec_builtins\n");
			exit_code(1, 0);
			// print_arr(tokens->args, "args");
			// printf("DOES IT COME IN HERE\n");
			exec_builtins(data, tokens->args[data.i]);
		}
		else if (find_passage(&data, "PATH", 1) == -1)
		{
			call_cmd_error(tokens->args[data.i], NULL, NO_CMD, -10);
		}
		// free_string(data.tmp->env_line);
		// printf("\t\texit code after = %d\n", exit_code(0, 0)); // just want to retrieve it
		data.i++;
	}
	return (0);
}
