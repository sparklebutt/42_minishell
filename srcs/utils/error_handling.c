/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:24:33 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/13 10:20:40 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	call_cmd_error(char *cmd, char *arg, int ret_value)
{
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
	char *error_msg;
	char *temp;

	temp = ft_strjoin("minishell: ", cmd);
	error_msg = ft_strjoin(temp, ": ");
	free(temp);
	if (arg != NULL)
	{
		temp = ft_strjoin(error_msg, arg);
		free(error_msg);
		error_msg = temp;
	}
	perror(error_msg);
	free(error_msg);
}
