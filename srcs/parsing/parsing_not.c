/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_not.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:00:43 by araveala          #+#    #+#             */
/*   Updated: 2024/08/08 16:20:16 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"



void collect_cmd_array(t_data *data, t_tokens *tokens, char *string)
{
	int x;
	x = total_words_c(string, ' ');
	tokens->args = ft_split_adv(string, ' ');
	if (check_open_quotes(tokens) < 0)
		return ;
	expansion_parser(tokens, data);
	pipe_collector(tokens, tokens->args);
	tokens->array_count = x;
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
int send_to_forks(t_data *data)
{
	if (data->tokens->pipe_count > 0)
	{
		if (pipe_fork(data) == -1)
			return (-1);
		return (2);
	}
	else if (data->tokens->pipe_count == 0)
	{
		check_path(data->tmp->env_line, 1, data, data->i);
		set_array(data);
		set_env_array(data);
		if (simple_fork(data) == 0)
			ft_printf("test\n"); // add error handling here
			//collective_free(data->tmp->filename, NULL, data->tmp->array); //this free was causing double free problems
		free_array(data->env_array);
		// free other arrays if needed / there are leaks
	}
	return(1);
}

int	find_passage(t_data *all, char *string, int divert)
{
	if(null_check(all->env->key, all->env, string) != 1)
		return (-1);
	if (find_node(all->env, string, all) == 1 && all->tmp->env_line != NULL)
	{
		if (divert == 2)
		{
			if (check_dir(all->tmp->env_line) == 0)
				return (free_extra_return_function(all->tmp->env_line, -1));
			return(1);
		}
		else
		{
			if (send_to_forks(all) == -1)
				return (-1);
			// ft_printf("end of send to forks\n");
		}
	}
	return (1);
}


static void	split_diversion(t_data *data, int divert, char *string)
{
	if (divert == 1) // PATH
		data->tmp->array = ft_split(string, ':');
	else if (divert == 2) // HOME
		data->tmp->array = ft_split(string, ' ');
	if (data->tmp->array == NULL)
	{
		printf("temp[i] is null for some reason\n"); // figure out what kind of error message is needed
	}
}

static char *take_end(char *new,  char *str, int start)
{
	size_t i;

	i = 0;
	while (str[start] != '\0')
	{
		new[i] = str[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return  (&*new);
}

int	check_path(char *string, int divert, t_data *all, int x)
{
	struct dirent	*dp;
	DIR				*dir; 
	char			*suffix;
	size_t			cmd_len;
	int				i;

	i = 0;
	suffix = NULL;
	cmd_len = ft_strlen(all->tokens->args[x]);
	
	///new
	if (all->tokens->args[x][0] == '/')
	{
		printf("checkcheck\n");
		size_t len = 0;
		len = ft_strlen(all->tokens->args[x]);
		while (len > 0)
		{
			if (all->tokens->args[x][len] == '/')
			{
				printf("what char we on look = %c len = %zu\n", all->tokens->args[x][len], len);
				break ;
			}
			len--;
		}
		char *path = NULL;
		char *cmd_n = NULL;
		path = malloc(sizeof(char *) * len + 2);
		path = ft_strncpy(path, all->tokens->args[x], len);//len);//ft_strdup(, len + 1);
		printf("do we have our path = %s\n", path);
		i = 0;
		if (check_dir(path) == 0)
			printf("dir fail\n");
		else
		{
			cmd_n = malloc(sizeof(char *) * len + 2);
			cmd_n = take_end(cmd_n, all->tokens->args[x], len); 
			free_string(all->tmp->filename);
			all->tmp->filename = all->tokens->args[x];//ft_strjoin(all->tmp->array[i], suffix);
//			free_string(suffix);
			if (all->tokens->pipe_count > 0)
				free_array(all->tmp->array);
			printf("dir success\n");
			return (1);
		}
	}
	///new ends

	if (all->tokens->args[x][0] != '/')
		suffix = ft_strjoin("/", all->tokens->args[x]);
	ft_printf("suffix = %s\n", suffix);	
	if (suffix == NULL || cmd_len == 0)
		return (free_extra_return_function(suffix, 0));
	split_diversion(all, divert, string);
	while (all->tmp->array[i])
	{
		if (check_dir(all->tmp->array[i]) == 1)
		{
			printf("looking for syntax = %s\n", all->tmp->array[i]);
			dir = opendir(all->tmp->array[i]);
			dp = readdir(dir);
			while (dp != NULL)
			{
				if (ft_strncmp(dp->d_name, all->tokens->args[x], cmd_len) == 0 && ft_strlen(dp->d_name) == cmd_len)
				{
					if (all->tmp->array[i] == NULL)
						return (-1);
					free_string(all->tmp->filename);
					all->tmp->filename = ft_strjoin(all->tmp->array[i], suffix);
					free_string(suffix);
					if (all->tokens->pipe_count > 0)
						free_array(all->tmp->array);
					closedir(dir);
					return (1);
				}
				dp = readdir(dir);
			}
			// closedir(dir); this was causing a leak of some kind
		}
		i++;
	}
	closedir(dir);
	//	return (free_extra_return_function(suffix, -1));
	collective_free(NULL, suffix, all->tmp->array);
	return (0);
}
