/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_adv_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:42:51 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 13:44:18 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_adv_loop(t_temps *tmp)
{
	tmp->word_len = 0;
	tmp->i = 0;
	tmp->flag = 0;
	tmp->x = 0;
	tmp->check = 0;
}

int	get_word_len(int *check, int *x)
{
	int	word_len;

	word_len = 0;
	if (*check > *x)
		word_len = (*check) - (*x);
	else
		word_len = (*x) - (*check);
	return (word_len);
}
