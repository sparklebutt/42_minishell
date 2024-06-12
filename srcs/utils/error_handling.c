/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:24:33 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/12 15:10:58 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_error(char *cmd, char *arg, char *msg)
{
	char *error_msg;
	char *temp;
	(void)msg;

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
