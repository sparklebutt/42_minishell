/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:24:33 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/10 12:50:16 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exit_code(int flag, int num)
{
	static int error_code = 0;
	if (flag) 
	{
		// printf("\t\tsetting error code to = %d\n" ,num);
		error_code = num;
	}// not 0
	
	return (error_code);
}

void	not_perror(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (arg != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	exit_code(1,1);
}

int	call_cmd_error(char *cmd, char *arg, char *msg, int ret_value)
{
	if (ret_value == -10)
	{
		not_perror(cmd, arg, msg);
		exit_code(1, 127);
		return (-1);
	}
	cmd_error(cmd, arg);
	return (ret_value);
}

t_env	*call_env_error(char *cmd, char *arg)
{
	cmd_error(cmd, arg);
	return (NULL);
}

void	cmd_error(char *cmd, char *arg)
{
	char	*error_msg;
	char	*temp;

	temp = NULL;
	error_msg = ft_strjoin("minishell: ", cmd);
	if (arg != NULL)
	{
		temp = ft_strjoin(error_msg, ": ");
		free_string(error_msg);
		error_msg = ft_strjoin(temp, arg);
	}
	if (temp != NULL)
		free_string(temp);
	perror(error_msg);
	free_string(error_msg);
	exit_code(1, 1);
}
