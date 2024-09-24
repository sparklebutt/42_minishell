/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:11:33 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/24 17:48:04 by vkettune         ###   ########.fr       */
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
	char	*temp;
	int		code;

	temp = NULL;
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
