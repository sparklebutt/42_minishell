/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:05:22 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/06 16:01:58 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int if_break(char *str)
{
	if (str[0] == '|')
		return (1);
	else if (str[0] == '<')
		return (1);
	else if (str[0] == '>')
		return (1);
	return (0);
}

int no_newline(char **args, int i)
{
	int j;

	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		while (args[i] && args[i][j] && args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
			i++;
		else
			break ;
	}
	return (i);
}

void	ft_echo(t_data *data, char **args) 
{
	int i;
	int nl;
	
	nl = no_newline(args, 1);
	i = data->i + nl; // mui importanto, no remove!
	/*~~ this skips past the echo itself, since we already now we have echo~~*/
	while (args[i])
	{
		if (if_break(args[i]) == 1)
			break;
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (nl == 1)
		ft_putchar_fd('\n', 1);
}
