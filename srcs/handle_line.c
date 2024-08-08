/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:17:55 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/06 10:52:34 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*~~ i removed the envs parameter as i need to be able to add pipe related
parameters and we can bring envs in inside the fucntion 
it is possible however they are not needed after all ~~*/
int	exec_builtins(t_data data, char *cmd, int fd, int r_w)
{
	t_env		envs;		
	t_tokens	*tokens;

	if (fd == 9 || r_w == 9)
		printf("holding incase we need these parameters");
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
	return (0);
}

int	handle_line(t_data data, t_tokens *tokens)
{
	data.tokens = tokens;
	if (tokens->args[0] == NULL)
		return (0);
	if (tokens->args[data.i] != NULL)
	{
		// ft_printf("we are now following the data i = %d\n", data.i);
		/*~~ im not sure but it might be possible to simplify 
		 can all of this run through the same fucntion clean and easy ~~*/
		if (tokens->pipe_count == 0 && is_builtins(tokens->args[data.i]) == 1)
		{
			exec_builtins(data, tokens->args[data.i], 0, 0); //send empty for fd
		}
		else if (find_passage(&data, data.i, "PATH", 1) == -1)
		{
			call_cmd_error(tokens->args[data.i], NULL, "command not found\n", -10);
		}
		data.i++;
	}
	return (0);
}
