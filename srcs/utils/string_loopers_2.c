/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_loopers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:08:22 by araveala          #+#    #+#             */
/*   Updated: 2024/09/21 11:38:38 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_echo_loop(char **args, int *x, int *i)
{
	char	*temp;

	(*x) = ft_strlen(args[*i]) + 2;
	temp = ft_calloc(*x, sizeof(char));
	if (temp == NULL)
		return (not_perror("echo", NULL, "malloc fail\n"), -1);
	temp[0] = 0x06;
	ft_strcpy(temp + 1, args[*i]);
	free_string(args[*i]);
	args[*i] = ft_strdup(temp);
	free_string(temp);
	(*i)++;
	(*x) = 0;
	return (0);
}

int	parse_redir_loop(t_data *data, int *i, int *x)
{
	char	**args;
	int		fd;

	fd = 0;
	args = data->tokens->args;
	if (ft_strlen(args[*i]) == 2 && ft_strncmp(args[*i], "<<", 2) == 0)
		heredoc_loop(data, data->tokens, args[*i + 1]);
	else if (args[*i + 1] != NULL && is_redirect(args[*i]) == 1)
		input_helper(data->tokens, fd, *i);
	else if (args[*i + 1] != NULL && (ft_strncmp(args[*i], ">>", 2) == 0
			|| ft_strncmp(args[*i], ">", 1) == 0))
		output_helper(data->tokens, fd, *i, *x);
	return (0);
}

void	redir_collect_loop(char **array, int i, int *count)
{
	if (ft_strlen(array[i]) > 2)
	{
		if (array[i][2])
			not_perror("syntax error", NULL, "too many redirects\n");
	}
	(*count)++;
}

void	add_redir_count(int token_count, int *count, int *comp_count)
{
	token_count++;
	(*comp_count) = (*count);
}
