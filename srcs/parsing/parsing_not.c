/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_not.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:00:43 by araveala          #+#    #+#             */
/*   Updated: 2024/07/12 14:50:16 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

// note that running cd .. ls(or other) or cd ../ ls(or other) , only take you back a dir, does not interact with other commands 

// the idea now is that i split the readline by space into a 2d array, i am not considering if there are spaces inbetween quotes with commands eg "ls    " | grep "objs    " , this should command not found anyway
// flags will also be seperate 

// string is rl
void collect_cmd_array(t_tokens *tokens, char *string)
{
	int x;

	x = total_words_c(string, ' ');
	tokens->args = ft_split_adv(string, ' '); // only double, no single
	if (check_open_quotes(tokens) < 0)
		return ;
	expansion_parser(tokens);
	pipe_collector(tokens, tokens->args);
	tokens->array_count = x;
	if (tokens->args == NULL)
	{
		ft_printf("malloc fail in parsing , making of array of args\n");
		return ;
	}
}

int	null_check(char *str1, t_env *str2, char *str3)
{
	
	if (str1 == NULL)
	{
		ft_printf("ENVS KEY NULL \n");
		return (0);
	}
	if (str2 == NULL)
	{
		ft_printf("ENVS IS NULL\n");
		return (0);
	}
	if (str3 == NULL)
	{
		ft_printf("STRING IS NULL"); // may not need this check, sofar alwasy hardcoded
		return (-1);
	}
	else
	{
		
		return (1);
	}
}

///***testing if this works
static int send_to_forks(t_data *data, int i)
{
	int r;

	r = 0;
	if (data->tokens->pipe_count > 0)
	{
		// ft_printf("its piping time|||||||\n");
		// ft_printf("0 = %s", data->tmp->ex_arr[0]);
		// ft_printf("0 = %s", data->tmp->ex_arr[1]);
		// ft_printf("0 = %s", data->tmp->ex_arr[2]);
		// ft_printf("0 = %s", data->tmp->ex_arr[3]);
		pipe_fork(data, data->i);
		return (2);
	}
	else if (data->tokens->pipe_count == 0)
	{
		set_array(data, i);	// if we need any of this data, we should not free yet
		if (simple_fork(data) == 0)
			collective_free(data->tmp->filename, NULL, data->tmp->array);
	}
	return(1);
}


int	find_passage(t_data *all, int i, char *string, int divert)
{
	int path_found;

	path_found = 0;
	if (i > 0)
		ft_printf("i is obsolete i think\n");
	if(null_check(all->env->key, all->env, string) != 1)
		return (-1);
	if (find_node(all->env, string, all) == 1 && all->tmp->env_line != NULL)
	{
		
		if (divert == 2)
		{
			// ft_printf("is this for home \n");
			if (check_dir(all->tmp->env_line) == 0)
				return (free_extra_return_function(all->tmp->env_line, -1));
			// else
			// all->tmp->filename = ft_strdup(all->tmp->env_line);
			// return (free_extra_return_function(all->tmp->env_line, 1));
			return(1);
		}
		else
		{
			if (all->tokens->pipe_count > 0)
			{
				ft_printf("steping into find passage wih pipes \n");
				path_found = check_path(all->tmp->env_line, divert, all, all->i); // x);
				send_to_forks(all, all->i);// (all, x);
				ft_printf("end of send to forks\n");
			}
			else
			{
				path_found = check_path(all->tmp->env_line, divert, all, all->i);
				if (path_found > 0)
					send_to_forks(all, all->i); //(all, i);
			}
			ft_printf("who where?\n");
		}
	}
	if (path_found == 0)
		return (-1);
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
		printf("temp[i] is null for some reason\n"); // remove?
		// error
	}
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
	//set_token_len_arr(all);
	if (all->tokens->args[x] == NULL)
	{
		ft_printf("args[%d] is NULL\n", x);
		return (-1);
	}
	cmd_len = ft_strlen(all->tokens->args[x]);
	if (all->tokens->args[x][0] != '/')
		suffix = ft_strjoin("/", all->tokens->args[x]);
	ft_printf("suffix = %s\n", suffix);
	/*	else //this is for eg /bin/ls must figure this out still
	{
		if (check_dir("/bin") == 1)
		{
		// ft_printf("WE ARE IN YOU SON OF A BICH\n");
		// different fucntion
		// go through string , count len, work backwards untill \ reached - this from len
		// seperate /bin , check passage then send ls
		// suffix == // go reverse in the string, grab characters up to \
		// suffix = ft_strdup(all->tokens->args[0]);

			all->tmp->filename = all->tokens->args[0];
			if (simple_fork(all) == 0)
				return (1);
			return (-1);
		}
	return (-1);
	}*/
	if (suffix == NULL || cmd_len == 0)
		return (free_extra_return_function(suffix, 0));
	split_diversion(all, divert, string);
	while (all->tmp->array[i])
	{		
		if (check_dir(all->tmp->array[i]) == 1)
		{
			// ft_printf("tmp array = %s\n", all->tmp->array[i]);
			dir = opendir(all->tmp->array[i]);
			dp = readdir(dir);
			while (dp != NULL)
			{	
				if (ft_strncmp(dp->d_name, all->tokens->args[x], cmd_len) == 0 && ft_strlen(dp->d_name) == cmd_len)
				{
					ft_printf("PATH HAS BEEN VALIDATED\n");
					if (all->tmp->array[i] == NULL)
						return (-1);
					all->tmp->filename = ft_strjoin(all->tmp->array[i], suffix);
					free(suffix);
					closedir(dir);
					return (1);
				}
				dp = readdir(dir);
			}
		}
		i++;
	}
	closedir(dir);
	// else
	//		return (free_extra_return_function(suffix, -1));
	// i++;
	collective_free(NULL, suffix, all->tmp->array);
	return (0);
}
