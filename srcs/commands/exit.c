/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:11:33 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/08 19:38:15 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit(char *cmd, t_tokens *tokens) // this should now be pretty good
{
	ft_printf("exit\n");
	if (tokens->array_count > 1)
	{
		if (atoi(tokens->args[1]) == 0)
			cmd_error(cmd, tokens->args[1], "numeric argument required\n");
		else if (tokens->array_count > 2)
			cmd_error(cmd, NULL, "exit: too many arguments\n");
		free(cmd);
		exit(0);
	}
	// add into envs $?
	free(cmd);
	exit(0);
	return (1);
}
