/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:05:22 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/27 10:13:42 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*~~ we need to run redirections throug here and i can not always be 1
carrying data should be enough to ensure we have access to enough information
for tweaking~~*/
void	ft_echo(t_data *data, char **args)
{
	int i;

	i = data->i + 1; // was 1, im not sure if we need + 1, or if we should increase data i somehwere instead
	dprintf(2, "running our own echo\n");
	while (args[i])
	{
		if (args[i][0] == '>')// || is_redirect(args[i]) != 0)
//		{
//			apply_redirections(data, data->tokens, data->x); // we could manage data x diff
			break ;			
//		}
		
		if (args[i][0] == '|')// || is_redirect(args[i]) != 0)
			break;
		ft_putstr_fd(args[i], 1);
		ft_putchar_fd(' ', 1);
		i++;

	}
	ft_putchar_fd('\n', 1);
}
