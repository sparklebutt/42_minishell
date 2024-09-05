/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_not.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:00:43 by araveala          #+#    #+#             */
/*   Updated: 2024/09/05 13:06:41 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clean_rest_of_quotes(t_data *data, int i, int len)// int x)
{
	char *new;

	new = NULL;
	if (data->simple == false)
	{
		if (data->tmp->exp_array[i])
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
	int	x;
	// int i = 0;

	x = total_words_c(string, ' ', data);
	tokens->args = ft_split_adv(string, ' ', data);
	tokens->heredoc = malloc(sizeof(char *) * 1);
	tokens->heredoc[0] = 0;
	if (check_open_quotes(tokens, 0, 0) < 0)
		return (1);
	expansion_parser(tokens, data);
	pipe_collector(tokens, tokens->args);
	create_redir_array(tokens);  // only mallocing
	redirect_collector(tokens, tokens->args, 0);
	if (parse_redirections(tokens, tokens->args, 0) == 1)
	{
		//printf("following process\n");
		return (1);
	}
	tokens->array_count = x; // was - 1
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

/*~~ stick this in fork_utils ~~*/
int	send_to_forks(t_data *data)
{
	// MARK
	//if (data->tokens->pipe_count > 0)
	//{
		if (pipe_fork(data) == -1)
			return (-1);
		return (2);
	//}
	/**~~ we might be able to remove the lower code completley , is it worth the work **/
	/*else if (data->tokens->pipe_count == 0)
	{
		
		//if (is_builtins(data->tokens->args[data->i]) != 1)
	//	{		 //	exec_builtins(*data, data->tokens->args[data->i]);
			//new code
		if (check_path(data->tmp->env_line, 1, data, data->i) == 0)
			return (-1);
		set_array(data);
	//	}
		set_env_array(data);
		if (simple_fork(data) == 0)
			ft_printf(""); // add error handling here
		free_array(data->env_array);
	}
	return (1);*/
}

int	find_passage(t_data *all, char *string, int divert)
{
	// printf("THIS IS IN FIND_PASSAGE\n");
	if (null_check(all->env->key, all->env, string) != 1)
	{
		// printf("ret - 1 null check\n");
		return (-1);
	}
	if (find_node(all->env, string, all) == 1 && all->tmp->env_line != NULL)
	{
		if (divert == 2)
		{
			if (check_dir(all->tmp->env_line) == 0)
			{
				// printf("ret - 1 cechk dir stuff\n");	
				return (free_extra_return_function(all->tmp->env_line, -1)); // not allowed
			}
			return (1);
		}
		else
		{	
			if (send_to_forks(all) == -1)
			{
				// printf("ret - 1 send to forks\n");
				return (-1);
			}
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
	{
		error("check dir", path);
		return (0);
	}
	else
	{
		cmd_n = ft_calloc(sizeof(char *), len + 1);
		cmd_n = take_end(cmd_n, all->tokens->args[x], len);
		all->tmp->filename = all->tokens->args[x];
		if (all->tokens->pipe_count > 0)
			free_array(all->tmp->array);
		return (1);
	}
}
