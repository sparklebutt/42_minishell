/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:14:55 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/18 11:25:15 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_flagged(t_data *data, char *new, int len, int i)
{
	char	**exp_array;
	char	*tmp;
	int		flag;

	tmp = NULL;
	exp_array = data->tmp->exp_array;
	flag = check_next(exp_array[i + 1], ft_strlen(exp_array[i]));
	if (ft_strchr(exp_array[i], '"') != NULL
		|| ft_strchr(exp_array[i], '\'') != NULL)
	{
		new = clean_quotes(exp_array[i], len, 0, 0);
		tmp = look_if_expans(data, data->env, new, flag);
		exp_array[i] = free_string(exp_array[i]);
		exp_array[i] = ft_strdup((tmp));
		tmp = free_string(tmp);
	}
	else
		exp_array[i] = look_if_expans(data, data->env, exp_array[i], flag);
}
