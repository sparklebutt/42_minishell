/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:11:33 by vkettune          #+#    #+#             */
/*   Updated: 2025/07/09 16:00:46 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

void	ft_exit(t_data *data, char *cmd, t_tokens *tokens)
{
	int		code;

	code = 0;
	ft_printf("exit\n");
	if (tokens->array_count > 1)
	{
		if (tokens->array_count > 2)
			return (not_perror(cmd, NULL, "too many arguments\n"));
		else if (tokens->args[1] != NULL && check_num(tokens->args[1]) == -1)
		{
			not_perror(cmd, tokens->args[1], "numeric argument required\n");
			code = 2;
		}
		else if (check_num(tokens->args[1]) == 0)
		{
			code = ft_atoi(tokens->args[1]);
			if (code > 255)
				code = code % 256;
		}
	}
	exit_code(1, code);
	free_n_exit(data, 0, 0);
}
