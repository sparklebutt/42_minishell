/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:17:55 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/10 15:42:34 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_builtins(t_data data, char *rl, char *cmd, int i)
{
	t_tokens *tokens;
	t_env *envs;
	
	tokens = data.tokens;
	envs = data.env; 
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (ft_exit(cmd, tokens));
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(&data, envs);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		ft_cd(&data, envs, i);
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

// fixed to handle multiple cmds ***FIND FIX // this is for easy find in vs code
//int	handle_line(t_data data, t_env envs, t_tokens *tokens, char *line)
int	handle_line(t_data data, t_tokens *tokens, char *line)
{
	//int i;

	//i = 0;
	data.tokens = tokens;
	//data.i = 0;
	if (tokens->args[0] == NULL)
		return (0);
	if (tokens->args[data.i] != NULL)	//if
	{
		if (is_builtins(tokens->args[data.i]) == 1)
		{
			exec_builtins(data, line, tokens->args[data.i], data.i);
		}
		else if (find_passage(&data, data.i, "PATH", 1) == -1)
		{
			
			call_cmd_error(tokens->args[data.i], NULL, "command not found\n", -10);
		}
		//i++;
		data.i++;
		//data.i = 0;
		
	}
	return (0);
}
