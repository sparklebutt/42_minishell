/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:05:22 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/09 10:35:43 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		if (args[i][0] == '|')
			break;
		ft_putstr_fd(args[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}
