/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_not.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:00:43 by araveala          #+#    #+#             */
/*   Updated: 2024/09/21 07:09:16 by vkettune         ###   ########.fr       */
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
	pipe_collector(tokens, tokens->args);
	if (tokens->redirect_count > 0 && create_redir_array(tokens) == -1)
		return (not_perror("redirect", NULL, "malloc fail\n"), 1);
	if (parse_redirections(data, tokens, tokens->args, 0) == -1)
		return (1);
	if (tokens->args == NULL)
		return (not_perror("parsing", NULL, "malloc fail\n"), 1);
	return (0);
}

int	find_passage(t_data *all, char *string, int divert)
{
	if (null_check(all->env->key, all->env, string) != 1)
		return (-1);
	if (find_node(all->env, string, all) == 1
		&& all->tmp->env_line != NULL && divert == 2)
	{
		if (check_dir(all->tmp->env_line) == 0)
			return (-1);
		return (1);
	}
	if (pipe_fork(all, 0, 0) == -1)
		return (-1);
	return (1);
}

int	find_len(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (len > 0)
	{
		if (str[len] == '/')
			break ;
		len--;
	}
	return (len);
}

int	handle_absolute_path(t_data *all, int x, char *path)
{
	size_t	len;

	len = find_len(all->tokens->args[x]);
	path = free_string(path);
	path = ft_calloc(sizeof(char), len + 1);
	path = ft_strncpy(path, all->tokens->args[x], len);
	if (check_dir(path) == 0)
	{
		error("check dir", path);
		path = free_string(path);
		return (0);//(exit_code(1, 0));
	}
	else
	{
		all->tmp->filename = all->tokens->args[x];
		path = free_string(path);
		return (1);
	}
	path = free_string(path);
	return (0);//exit_code(1, 0));
}
