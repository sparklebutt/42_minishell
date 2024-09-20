/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_adv_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:42:51 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/20 09:43:57 by vkettune         ###   ########.fr       */
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

char	*stupid_function(size_t *word, t_temps *tmp, const char *s)
{
	(*word)++;
	lol(&tmp->i, &tmp->x);
	return (ft_substr(s, tmp->word_len, 1));
}

void	stupid_function_2(int *words, int *i, const char *s, char c)
{
	(*words)++;
	(*i) += fancy_strlen(s, c, *i) - (*i);
	if (s[*i] && is_char_redir(s[*i - 1]) > 0 && is_char_redir(s[*i - 2]) == 0)
		(*i)--;
	else if (s[*i] && is_char_redir(s[*i - 1]) > 0
		&& is_char_redir(s[*i - 2]) > 0)
		(*i) -= 2;
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

