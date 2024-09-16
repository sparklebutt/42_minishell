/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_not.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:00:43 by araveala          #+#    #+#             */
/*   Updated: 2024/09/16 09:48:39 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clean_rest_of_quotes(t_data *data, int i, int len)// int x)
{
	char *new;

	// cut this smaller
	new = NULL;
	if (data->simple == false)
	{
		if (data->tmp->exp_array && data->tmp->exp_array[i])
		{
			if (ft_strchr(data->tmp->exp_array[i], '"') != NULL
			|| ft_strchr(data->tmp->exp_array[i], '\'') != NULL)
			{
				new = clean_quotes(data->tmp->exp_array[i], len, 0, 0);
				free_string(data->tmp->exp_array[i]);
				data->tmp->exp_array[i] = new;
			}
			else
			{
				new = clean_quotes(data->tmp->exp_array[i], len, 0, 0);
				free_string(data->tmp->exp_array[i]);
				data->tmp->exp_array[i] = new;
			}
		}
	}
	else if (data->tokens->args[i])
	{
		if (ft_strchr(data->tokens->args[i], '"') != NULL
		|| ft_strchr(data->tokens->args[i], '\'') != NULL)
		{
			new = clean_quotes(data->tokens->args[i], len, 0, 0);
			free_string(data->tokens->args[i]);
			data->tokens->args[i] = new;
		}
	}
	return (0);
}

int	collect_cmd_array(t_data *data, t_tokens *tokens, char *string)
{
	// cut this smaller
	// these 4 lines need to be here for now, or else redirs will segfault.
	// we need to change where heredocs are declared the first time, cause something needs to be there before child's are called
	// -------------------- ------------
	// if (tokens->heredoc != NULL)
	// 	free_array(tokens->heredoc);
	// tokens->heredoc = malloc(sizeof(char *) * 1);
	// tokens->heredoc[0] = 0;
	// ---------------------------------
	tokens->array_count = total_words_c(string, ' ', data);
	tokens->args = ft_split_adv(string, ' ', data);
	if (tokens->args == NULL)
		return (1);
	if (check_open_quotes(tokens, 0, 0) == -1)
	{
		printf("syntax error open quotes\n");
		return (1);
	}
	if (expansion_parser(tokens, data) == -1)
	{
		// free up to this point
		return (1);
	}
	pipe_collector(tokens, tokens->args);
	// can we put all of the 3 redir unctions and their if statements into one sub function that handles those??? idk just an idea
	// ----------------------------------------------------------------------
	redirect_collector(tokens, tokens->args, 0);
	if (tokens->redirect_count > 0 && create_redir_array(tokens) == -1) // only mallocing
	{
		// free up to this point
		return (1);
	}
	if (parse_redirections(data, tokens, tokens->args, 0) == 1)
	{
		printf("following process\n");
		return (1);
	}
	// ----------------------------------------------------------------------
	if (tokens->args == NULL)
	{
		ft_printf("malloc fail in parsing , making of array of args\n");
		return(1);
	}
	return (0);
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

int	find_passage(t_data *all, char *string, int divert)
{
	if (null_check(all->env->key, all->env, string) != 1)
	{
		printf("\t\tret - 1 null check\n");
		return (-1);
	}
	if (find_node(all->env, string, all) == 1 && all->tmp->env_line != NULL && divert == 2)
	{
		if (check_dir(all->tmp->env_line) == 0)
		{
			printf("\t\tret - 1 cechk dir stuff\n");
			return (free_extra_return_function(all->tmp->env_line, -1));
		}
		return (1);
	}
	if (pipe_fork(all) == -1)
	{
		// printf("\t\tret - 1 send to forks\n"); // below as in here !!!
		return (-1);
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
 	new[i] = 0; // valgrind did not like null character '\0' here for some reasonnnnn
 	return (new);
 }

int	handle_absolute_path(t_data *all, int x, char *path) // cut this smaller
{
	size_t	len;
	char	*cmd_n;
//	char *tmp;

	// cmd_n = path // old thing, but since we are only using it in one place where "path" is NULL
	// so this didn't make sense to me
	cmd_n = NULL;
//	tmp = NULL;
	len = ft_strlen(all->tokens->args[x]);
	while (len > 0)
	{
		if (all->tokens->args[x][len] == '/')
			break ;
		len--;
	}
	///// what is we need to check each dir , eg /usr/bin/ls, must split nto tiny tiny parts and chekdir
	// if (path != NULL) // maybe not needed
	free_string(path);
	path = ft_calloc(sizeof(char), len + 1); // this has issues, 84 blcoks of deff lost memory with parsing_script.sh and most from here, viilja
	path = ft_strncpy(path, all->tokens->args[x], len);
	if (check_dir(path) == 0)
	{
		error("check dir", path);
		free_string(path);
		return (0);
	}
	else
	{
		free_string(cmd_n);
		cmd_n = ft_calloc(sizeof(char), len + 2); // adding 2 here fixed a write error, check this out. It happens on ine 158 of this file aka [new[i] = 0;]
		cmd_n = take_end(cmd_n, all->tokens->args[x], len);
		free_string(cmd_n); // new free, fixed leaks. try parsing_stript.sh and you'll see a difference
		all->tmp->filename = all->tokens->args[x];
		free_string(path);
		return (1);
	}
	free_string(path);
	return (0);
}
