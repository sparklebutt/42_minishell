/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_not.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:00:43 by araveala          #+#    #+#             */
/*   Updated: 2024/09/18 11:59:04 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_extra_special_echo_case(t_tokens *tokens)
{
	int		i;
	int		x;
	char	*temp;

	x = 0;
	i = 0;
	temp = NULL;
	while (tokens->args[i] != NULL)
	{
		if (tokens->args[i][0] == '"' || tokens->args[i][0] == '\'')
		{
			while (tokens->args[i][x] && (tokens->args[i][x] == '"'
				|| tokens->args[i][x] == '\''))
				x++;
			if (tokens->args[i][x] == '|' || is_char_redirect(tokens->args[i][x]) > 0)
			{
				x = ft_strlen(tokens->args[i])  + 2;
				temp = ft_calloc(x, sizeof(char));
				if (temp == NULL)
				{
					// malloc fail exit_code and clean.
					return (-1); //for now , should be ft-exit
				}
				temp[0] = 0x06;
				ft_strcpy(temp + 1, tokens->args[i]);
				free_string(tokens->args[i]);
				tokens->args[i] = ft_strdup(temp);
				free_string(temp);
				i++;
				x = 0;
				continue;
			}
			i++;
			continue;
		}
		i++;
	}
	return (0);
}

int	collect_cmd_array(t_data *data, t_tokens *tokens, char *string)
{
	tokens->array_count = total_words_c(string, ' ', data);
	tokens->args = ft_split_adv(string, ' ', data);
	if (tokens->args == NULL)
		return (1);
	if (check_open_quotes(tokens, 0, 0) == -1
		|| redirect_collector(tokens, tokens->args, 0) == -1)
		return (1);
	expansion_parser(tokens, data);
	pipe_collector(tokens, tokens->args);
	if (tokens->redirect_count > 0 && create_redir_array(tokens) == -1)
		return (not_perror("redirect", NULL, "malloc fail"), 1);
	if (parse_redirections(data, tokens, tokens->args, 0) == -1)
		return (1);
	if (tokens->args == NULL)
		return (not_perror("parsing", NULL, "malloc fail"), 1);
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
	if (pipe_fork(all) == -1)
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
		return (0);
	}
	else
	{
		all->tmp->filename = all->tokens->args[x];
		path = free_string(path);
		return (1);
	}
	path = free_string(path);
	return (0);
}
