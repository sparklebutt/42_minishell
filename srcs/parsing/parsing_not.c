/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_not.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:00:43 by araveala          #+#    #+#             */
/*   Updated: 2024/09/23 17:44:17 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_extra_special_echo_case(char **args)
{
	int		i;
	int		x;

	x = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] == '"' || args[i][0] == '\'')
		{
			while (args[i][x] && (args[i][x] == '"'
				|| args[i][x] == '\''))
				x++;
			if (args[i][x] == '|' || is_char_redir(args[i][x]) > 0)
			{
				if (special_echo_loop(args, &x, &i) == -1)
					return (-1);
				continue ;
			}
			i++;
			continue ;
		}
		i++;
	}
	return (0);
}

int	collect_cmd_array(t_data *data, t_tokens *tokens, char *string)
{
	tokens->array_count = total_words_c(string, ' ');
	tokens->args = ft_split_adv(string, data);
	if (tokens->args == NULL)
		return (1);
	if (check_open_quotes(tokens, 0, 0) == -1)
		return (1);
	if (redirect_collector(tokens, tokens->args, 0, 0) == -1)
		return (1);
	check_extra_special_echo_case(tokens->args);
	expansion_parser(tokens, data);
	if (pipe_collector(tokens, tokens->args) == -1)
		return (1);
	if (tokens->redirect_count > 0 && create_redir_array(tokens) == -1)
		return (not_perror("redirect", NULL, "malloc fail\n"), 1);
	if (parse_redirections(data, tokens, tokens->args, 0) == -1)
		return (1);
	if (tokens->args == NULL)
		return (not_perror("parsing", NULL, "malloc fail\n"), 1);
	return (0);
}

int	find_passage(t_data *data, char *string, int divert)
{
	if (null_check(data->env->key, data->env, string) != 1)
		return (-1);
	if (find_node(data->env, string, data) == 1
		&& data->tmp->env_line != NULL && divert == 2)
	{
		if (check_dir(data->tmp->env_line) == 0)
			return (-1);
		return (1);
	}
	// data->tmp->env_line = free_string(data->tmp->env_line);
	if (pipe_fork(data, 0, 0) == -1)
		return (-1);
	return (1);
}
