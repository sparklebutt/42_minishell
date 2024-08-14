/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_not.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:00:43 by araveala          #+#    #+#             */
/*   Updated: 2024/08/13 17:51:50 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	collect_cmd_array(t_data *data, t_tokens *tokens, char *string)
{
	int	x;

	x = total_words_c(string, ' ');
	tokens->args = ft_split_adv(string, ' ');
	if (check_open_quotes(tokens, 0, 0) < 0)
		return ;
	expansion_parser(tokens, data);
	parse_redirections(tokens, tokens->args, 0);
	pipe_collector(tokens, tokens->args);
	redirect_collector(tokens, tokens->args);
	tokens->array_count = x; // was - 1
	if (tokens->args == NULL)
	{
		ft_printf("malloc fail in parsing , making of array of args\n");
		return ;
	}
}

int	null_check(char *str1, t_env *str2, char *str3) // might not be needed
{
	if (str1 == NULL || str2 == NULL)
	{
		if (str1 == NULL)
			ft_printf("ENVS KEY NULL \n");
		else if (str2 == NULL)
			ft_printf("ENVS IS NULL\n");
		return (0);
	}
	if (str3 == NULL)
	{
		ft_printf("STRING IS NULL");
		return (-1);
	}
	return (1);
}

/*~~ stick this in fork_utils ~~*/
int	send_to_forks(t_data *data)
{
	// printf("AAAAA\n");
	if (data->tokens->pipe_count > 0)
	{
		if (pipe_fork(data) == -1)
			return (-1);
		// printf("exiting\n");
		return (2);
	}
	else if (data->tokens->pipe_count == 0)
	{
		if (check_path(data->tmp->env_line, 1, data, data->i) == 0)
			return (-1);
		set_array(data);
		set_env_array(data);
		if (simple_fork(data) == 0)
			ft_printf("no fork needed\n"); // add error handling here
		free_array(data->env_array);
	}
	return (1);
}

int	find_passage(t_data *all, char *string, int divert)
{
	printf("THIS IS IN FIND_PASSAGE\n");
	if (null_check(all->env->key, all->env, string) != 1)
		return (-1);
	if (find_node(all->env, string, all) == 1 && all->tmp->env_line != NULL)
	{
		if (divert == 2)
		{
			if (check_dir(all->tmp->env_line) == 0)
				return (free_extra_return_function(all->tmp->env_line, -1));
			return (1);
		}
		else
		{
			
			printf("check if needs to send to fork\n");
			if (send_to_forks(all) == -1)
			{
				//printf("here????\n");
				return (-1);
			}
			// printf("after simple fork\n");
			// ft_printf("end of send to forks\n");
		}
	}
	return (1);
}

static char	*take_end(char *new, char *str, int start)
{
	size_t	i;

	i = 0;
	while (str[start] != '\0')
	{
		new[i] = str[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (&*new);
}

int	handle_absolute_path(t_data *all, int x, char *path)
{
	size_t	len;
	char	*cmd_n;

	cmd_n = path;
	len = ft_strlen(all->tokens->args[x]);
	while (len > 0)
	{
		if (all->tokens->args[x][len] == '/')
			break ;
		len--;
	}
	path = ft_calloc(sizeof(char *), len + 1);
	path = ft_strncpy(path, all->tokens->args[x], len);
	if (check_dir(path) == 0)
		return (error("check dir", path));
	else
	{
		cmd_n = ft_calloc(sizeof(char *), len + 1);
		cmd_n = take_end(cmd_n, all->tokens->args[x], len);
		// free_string(all->tmp->filename); // for testing
		all->tmp->filename = all->tokens->args[x];
		if (all->tokens->pipe_count > 0)
			free_array(all->tmp->array);
		printf("dir success\n"); // for testing
		return (1);
	}
}
