/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_not.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:00:43 by araveala          #+#    #+#             */
/*   Updated: 2024/05/29 12:56:57 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

// note that running cd .. ls(or other) or cd ../ ls(or other) , only take you back a dir, does not interact with other commands 

// the idea now is that i split the readline by space into a 2d array, i am not considering if there are spaces inbetween quotes with commands eg "ls    " | grep "objs    " , this should command not found anyway
// flags will also be seperate 

// string is rl
void collect_cmd_array(t_tokens *tokens, char *string)
{
	int i;
	int x;
	char *tmp;

	x = total_words_c(string, ' ');
	i = 0;
	// spit adv has some double quotes handing just for example
	tokens->args = ft_split_adv(string, ' ');
	tmp = NULL;
	pipe_collector(tokens, tokens->args); //maybe dont need
	tokens->array_count = x;
	if (tokens->args == NULL)
	{
		ft_printf("malloc fail in parsing , making of array of args\n");
		return ;
	}	
	i = 0;
	mini_parser(tokens, i, x); //changing CD to cd for example
	// some error handling maybe?
}

void	find_passage(t_data *all, char *string, int divert)
{
	// if command is not a built in command
	int strlen;

	if (all->tokens->args == NULL || all->tokens->args[0] == NULL) // cmd is the same as a->t>a[0]
	{
		printf("ARGS NULL OHO \n");
		return;
	}
	ft_printf("cmd = %s\n", all->tokens->args[0]);
	if (all->env->key == NULL || all->env == NULL)
		printf("ENVS NULL OHO \n");
	if (string  == NULL)
		printf("STRING OR CMD  NULL OHO \n");
	strlen = ft_strlen(string);
	if (find_node(all->env, string, all) == 0 && all->tmp->env_line != NULL)
		check_path(all->tmp->env_line, divert, all);
}

static void	set_array(t_data *data)// char *flag, char *arguments)
{
	data->tmp->ex_arr[0] = data->tmp->filename;
	data->tmp->ex_arr[1] = NULL;//flag;
	data->tmp->ex_arr[2] = NULL; //arguments;
	data->tmp->ex_arr[3] = NULL; // last one is null
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

void	check_path(char *string, int divert, t_data *all)
{
	struct dirent	*dp;
	DIR				*test; 
	char			*suffix;
	size_t			cmd_len;
	int				i;

	i = 0;
	cmd_len = ft_strlen(all->tokens->args[0]);
	suffix = ft_strjoin("/", all->tokens->args[0]);
	if (suffix == NULL || cmd_len == 0)
		printf("malloc fail in check path bla or cmd len 0\n");
	split_diversion(all, divert, string);
	while (all->tmp->array[i] != NULL)
	{
		printf("temp i = %s\n", all->tmp->array[i]); // remove
		if (access(all->tmp->array[i], X_OK) == 0)
		{
			test = opendir(all->tmp->array[i]);
			if (test == NULL)
				printf("openddir FAIL\n\n"); // remove
			dp = readdir(test);
			if (dp == NULL)
				printf("readddir FAIL\n\n"); // remove
			if (divert == 2)
			{
				all->tmp->filename = all->tmp->array[i];
				free_string(suffix);
				closedir(test);
				return;
			}
			while (dp != NULL)
			{
				// printf("dp name = %s\n", dp->d_name); // remove
				if (ft_strncmp(dp->d_name, all->tokens->args[0], cmd_len) == 0 && ft_strlen(dp->d_name) == cmd_len)
				{			
					all->tmp->filename = ft_strjoin(all->tmp->array[i], suffix);
					set_array(all); //, NULL, NULL, NULL);
					printf("filename = %s\n", all->tmp->filename); // remove
					free_string(all->tmp->env_line);
					// execve will be sent to child from here
					execve(all->tmp->filename, all->tmp->ex_arr, NULL);
					free_string(all->tmp->filename);
					free(suffix);
					return;
				}
				dp = readdir(test);
			}
			closedir(test);
		}
		i++;
	}

}
