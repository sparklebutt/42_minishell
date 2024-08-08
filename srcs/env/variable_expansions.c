/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:03:23 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/08 11:55:39 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_key_len(char *str, int start)
{
	int len;
	len = start + 1;  // Start of key, after $
	while (str[len] && !(str[len] == ' ' || str[len] == '\0'
		|| str[len] == '"' || str[len] == '\''))
		len++;
	return (len - start - 1); // Length excluding $
}

char *new_str(char *str, char *value, int start, int end)
{
	int new_len;
	char *new_str;

	new_len = start + strlen(value) + strlen(str + end) + 1;
	new_str = malloc(sizeof(char) * new_len);
	if (!new_str)
		return NULL;
	ft_strncpy(new_str, str, start);
	ft_strcpy(new_str + start, value);
	ft_strcpy(new_str + start + ft_strlen(value), str + end);
	return (new_str);
}

char *remove_key(char *str, int start, int end)
{
	int new_len;
	char *new_str;

	new_len = start + strlen(str + end) + 1;
	new_str = malloc(sizeof(char) * new_len);
	if (!new_str)
		return NULL;
	ft_strncpy(new_str, str, start);
	ft_strcpy(new_str + start, str + end);
	return (new_str);
}

char *replace_expansion(t_data *data, t_env *envs, char *arg, int start)
{
	int key_len;
	char *temp_key;
	char *value = NULL;
	char *new_arg = NULL;

	key_len = find_key_len(arg, start);
	temp_key = malloc(sizeof(char) * (key_len + 1));
	if (!temp_key)
		return NULL;
	ft_strncpy(temp_key, arg + start + 1, key_len);
	temp_key[key_len] = '\0';
	if (find_node(envs, temp_key, data) == 1)
	{
		value = find_keys_value(envs, temp_key);
		if (value != NULL)
			new_arg = new_str(arg, value, start, start + key_len + 1);
		else
			new_arg = remove_key(arg, start, start + key_len + 1);
		free(arg);
	}
	printf("bug hunting2 new arg = %s\n", new_arg);	
	free(temp_key);
	/*~~ new arg is showing null here for some reason after trying to expand a exported varaible ~~*/
	return (new_arg);
}

char *look_if_expansions(t_data *data, t_env *envs, char *arg)
{
	int i = 0;
	while (arg[i])//&& arg[i] != '\n')
	{
		if (arg[i] == '$')
		{
			printf("\tit gets here!\n");
			arg = replace_expansion(data, envs, arg, i);
			i = -1; // start from 0 and look through the arg again
		}
		i++;
	}
	return (arg);
}

char **variable_expansions(t_data *data, t_env *envs, char **args)
{
	int i = 0;
	while (args[i] != NULL)
	{
		/*~~  does not seem to handle if there are no quotes right ~~*/
		printf("arg[%d] = %s\n", i, args[i]);
		args[i] = look_if_expansions(data, envs, args[i]);
		i++;
	}
	// printf("the end\n");
	return (args);
}
