/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:40:21 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/18 11:57:07 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code(int flag, int num)
{
	static int	error_code = 0;

	if (flag)
		error_code = num;
	return (error_code);
}

char	*replace_exitcode(char *arg, int start)
{
	char	*value;
	char	*new_arg;

	value = ft_itoa(exit_code(0, 0));
	new_arg = new_str(arg, value, start, start + 1 + 1);
	value = free_string(value);
	arg = free_string(arg);
	return (new_arg);
}
