/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:00:43 by araveala          #+#    #+#             */
/*   Updated: 2024/05/23 18:36:09 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

//note that running cd .. ls(or other) or cd ../ ls(or other) , only take you back a dir, does not interact with other commands 

//the idea now is that i split the readline by space into a 2d array, i am not considering if there are spaces inbetween quotes with commands eg "ls    " | grep "objs    " , this should command not found anyway
//flags will also be seperate 

void	pipe_collector(t_tokens *tokens, char **array)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (array[i] != '\0')
	{
		if (array[i][0] == '|')
		{

			count++;
			//splt already confirmed spaces around pipe
			//what if pipe is the last char with no feed, it takes input differently
		}
		i++;
	}
	tokens->pipe_count = count;
	printf("we have %d pipes\n", tokens->pipe_count);
}

//string is rl
//rename to collect array data
void collect_cmd_array(t_tokens *tokens, char *string)
{
	int i;
	int x;

	x = 8;//get array count or make split finish array with null
	i = 0;
	
	//spit does not consider if string has multiple spaces to print, will split spaces away.
	//could consider placeholder for delimeter ooor we will navigate rl to compare and find strings to print   
	// quotes should be a safe space for spaces

	tokens->args = ft_split(string, ' ');
	pipe_collector(tokens, tokens->args); //maybe dont need
	//maybe special char collector? such as &&
	if (tokens->args == NULL)
	{
		ft_printf("malloc fail in parsing , making of array of args\n");
		return ;
	}	
	i = 0;

//just so we can see insideVVV
	while (i != x)//causes->segv(&command_array[i + 1] != NULL) 
	{
		printf("looking inside array in struct = %s\n", tokens->args[i]);
		i++;
	}
//some error handling maybe?
}

void	find_passage(t_env *envs, char *string, char *cmd)
{
	//string eg PATH || HOME 
	//BEWARE check path_bla is desgined to work with  PATH at this moment
	//if command is not a built in command
	int strlen;

	strlen = ft_strlen(string);
	while (envs->next != NULL)
	{
		envs = envs->next;
//		printf("envs key = %s\n", envs->key);
		if (ft_strncmp(envs->key, string, strlen) == 0)
		{
			check_path_bla(envs->value, cmd, 1);//using flag for now for path
			printf("we found passage for commands\n");
		}	
	}
	if (envs == NULL)
		printf("holding position \n");
	//clean stuff
	}

///THIS IS A CO,PLETE MESS AND I LOST HOPE  
void	check_path_bla(char *string, char *cmd, int flag)
{
	struct dirent *dp; //dp = dir pointer, struct required 
	DIR *test; 

	char **temp;
	char *filename;
	char *suffix;// "/ + cmd"
	size_t	 cmd_len; //size t because strlen returns size t
	int i;
//	char *why[] = {cmd, NULL};

	i = 0;

	temp = NULL;
	cmd_len = ft_strlen(cmd);
	filename = NULL;
	suffix = ft_strjoin("/", cmd);
	if (suffix == NULL)
		printf("malloc fail in check path bla\n");
	if (flag == 1) //PATH
		temp = ft_split(string, ':');
	else if (flag == 2)
		//temp = set up home
	printf("bug huntning \n");
	while (temp[i] != NULL)
	{
		printf("temp i = %s\n", temp[i]);
		if (access(temp[i], X_OK) == 0)
		{
			printf("access says ok to DIR\n");
			test = opendir(temp[i]);
			printf("we opened dir\n");
			//if test null check


			while((dp = readdir(test)) != NULL)// (dp != NULL)
			{


				if (ft_strncmp(dp->d_name, cmd, cmd_len) == 0 && ft_strlen(dp->d_name) == cmd_len)//otherwise we do not find exact cmd
				{
					filename = ft_strjoin(temp[i], suffix);
					printf("filename = %s\n", filename);
//					execve(cmd, why, &temp[i]);
					printf("are we execut~~~~~~~~~~~~~e\n");

				}
//				dp = readdir(test);
//				if (dp == NULL)
//					printf("let me know\n");
//				printf("looking for whats in dir = %s\n", dp->d_name);
			}
			closedir(test);
			printf("close dir 1\n");
			if (filename != NULL)
			{
				free(filename);
				filename = NULL;
			}
			if (suffix != NULL)
			{
				free(suffix);
				suffix = NULL;
			}
			closedir(test);
			printf("we close dirwtf\n");
		}
		i++;
		
	}
//	free(suffix);
}
