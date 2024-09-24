/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:14:55 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/24 18:11:44 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stupid_function_3(t_tokens *tokens, int *quote_count, int i, int *x)
{
	tokens->quote = 1;
	if ((int)ft_strlen(tokens->args[i]) > 1)
		(*quote_count) = loop_quotes(tokens, *quote_count, i, x);
}

int	checks_before_redir(t_data *data, char **args)
{
	while (args[data->i] != NULL && args[data->i][0] != '|'
			&& is_redirect(args[data->i]) > 0)
	{
		set_bools(data, args[data->i]);
		data->i += 2;
	}
	if (args[data->i] != NULL && args[data->i][0] == '|')
	{
		data->i++;
		return (0);
	}
	if (args[data->i] != NULL && check_path(data->tmp->env_line,
			1, data, data->i) == 0)
		return (-1);
	return (0);
}

int	free_string_2(char *str, int ret)
{
	str = free_string(str);
	return (ret);
}
