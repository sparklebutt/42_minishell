/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:00:43 by araveala          #+#    #+#             */
/*   Updated: 2024/05/24 13:32:22 by araveala         ###   ########.fr       */
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
	int len;

	i = 0;
	count = 0;
	while (array[i] != '\0')
	{
		len = ft_strlen(array[i]);

		if (array[i][0] == '|')
		{
			if (len == 2)
			{
				if (array[i][1] == '|')
					printf("we have 2 pipes next to eachother BONUS POTENTIAL\n");
					//we can do a count and mark special char for bonuse here
			}
			if (len > 2)
			{

				if (array[i][2] == '|')
					printf("syntax error , too many pipes STEP BACK TO MAIN\n");
			}
			count++;
			//splt already confirmed spaces around pipe
			//pipe as last char needs to be handled
		}
		i++;
	}
	tokens->pipe_count = count;
	printf("we have %d pipes\n", tokens->pipe_count);
}

//string is rl
void collect_cmd_array(t_tokens *tokens, char *string)
{
	int i;
	int x;

	x = total_words_c(string, ' ');
	i = 0;
//spit adv has some double quotes handing just for example
	tokens->args = ft_split_adv(string, ' ');
	pipe_collector(tokens, tokens->args); //maybe dont need
	if (tokens->args == NULL)
	{
		ft_printf("malloc fail in parsing , making of array of args\n");
		return ;
	}	
	i = 0;
//just so we can see inside
	while (i != x)
	{
		//we can loop though to find syntax errors here, eg | | is a syntax error
		//we can also collect special chars here or just after pipe collector
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

	if (envs == NULL)
		printf("ENVS NULL OHO \n");
	if (string  == NULL || cmd == NULL)
		printf("STRING OR CMD  NULL OHO \n");

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
	//clean stuff
	}


void	check_path_bla(char *string, char *cmd, int flag)
{
	struct dirent *dp; //dp = dir pointer, struct required 
	DIR *test; 

	char **temp;
	char *filename;
	char *suffix;// "/ + cmd"
	size_t	 cmd_len; //size t because strlen returns size t
	int i;

	i = 0;
	temp = NULL;
	filename = NULL;
	cmd_len = ft_strlen(cmd);
	suffix = ft_strjoin("/", cmd);

	if (suffix == NULL)
		printf("malloc fail in check path bla\n");
	if (flag == 1) //PATH
		temp = ft_split(string, ':');
	if (flag == 2)
		//temp = set up home
	if (temp == NULL || temp[i] == NULL)
		printf("temp[i] is null for some reason\n");
	while (temp[i] != NULL)
	{
		printf("temp i = %s\n", temp[i]);
		if (access(temp[i], X_OK) == 0)
		{
			printf("access says ok to DIR\n");
			test = opendir(temp[i]);
//			if (test == NULL)
//				printf("what what in the butt\n");
			printf("we opened dir\n");
			while((dp = readdir(test)) != NULL)// work arouund needed here
			{
				if (ft_strncmp(dp->d_name, cmd, cmd_len) == 0 && ft_strlen(dp->d_name) == cmd_len)//otherwise we do not find exact cmd
				{

					filename = ft_strjoin(temp[i], suffix);
					printf("filename = %s\n", filename);
//					execve(cmd, why, &temp[i]);
					printf("are we execut~~~~~~~~~~~~~e\n");
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
					printf("succed so then we leav~~~~~~~~~~~~~e\n");
					return;
				}
//				dp = readdir(test);
//				if (dp == NULL)
//					printf("let me know\n");
//				printf("looking for whats in dir = %s\n", dp->d_name);
			}
			closedir(test);
			printf("close dir 1\n");
		}
		i++;
		
	}
//	free(suffix);
}
