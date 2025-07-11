/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:05:22 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 17:21:10 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_break(char *str)
{
	if (str[0] == 0x06)
		return (0);
	if (ft_strlen(str) > 2)
		return (0);
	if (str[0] == '|')
		return (1);
	else if (str[0] == '<')
		return (1);
	else if (str[0] == '>')
		return (1);
	return (0);
}

int	no_newline(char **args, int i)
{
	int	j;

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
	int	i;
	int	nl;

	nl = no_newline(args, 1);
	i = data->i + nl;
	while (args[i])
	{
		if (if_break(args[i]) == 1)
			break ;
		if (args[i][0] == 0x06)
			ft_putstr_fd(&args[i][1], 1);
		else
			ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL && args[i + 1][0] != '|'
			&& is_redirect(args[i + 1]) == 0)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (nl == 1)
		ft_putchar_fd('\n', 1);
}
