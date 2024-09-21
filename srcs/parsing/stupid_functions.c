/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:14:55 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 14:00:34 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	stupid_function_3(t_tokens *tokens, int *quote_count, int i, int *x)
{
	tokens->quote = 1;
	if ((int)ft_strlen(tokens->args[i]) > 1)
		(*quote_count) = loop_quotes(tokens, *quote_count, i, x);
}

void	why(char **new_heredoc, char **old_heredoc, int *i)
{
	new_heredoc[*i] = ft_strdup(old_heredoc[*i]);
	(*i)++;
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
		data->i++;
	if (args[data->i] != NULL
		&& check_path(data->tmp->env_line, 1, data, data->i) == 0)
		return (-1);
	return (0);
}
