/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:24:33 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/08 18:30:19 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_error(char *cmd, char *arg, char *msg)
{
	if (arg == NULL)
		ft_printf("minishell: %s: %s\n", cmd, msg);
	else
		ft_printf("minishell: %s: %s: %s\n", cmd, arg, msg);
	
}
