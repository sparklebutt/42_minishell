/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:03:23 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/04 17:38:57 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_key_len(char *str, int start)
{
	int	len;
	
	len = start + 1;
	while (str[len] && !(str[len] == ' ' || str[len] == '\0'
		|| str[len] == '"' || str[len] == '\'' || str[len] == '$'))
		len++;
	return (len - start - 1); // Length excluding $
}

char	*new_str(char *str, char *value, int start, int end)//, t_data *data)
{
	int		new_len;
	char	*new_str;
	new_len = start + strlen(value) + strlen(str + end) + 1;
	new_str = malloc(sizeof(char) * new_len);
	if (!new_str)
		return NULL;
	ft_strncpy(new_str, str, start);
	ft_strcpy(new_str + start, value);
	//data->prev_len = ft_strlen(new_str);
	ft_strcpy(new_str + start + ft_strlen(value), str + end);
	return (new_str);
}

char	*remove_key(char *str, int start, int end)
{
	int		new_len;
	char	*new_str;

	new_len = start + strlen(str + end) + 1;
	new_str = malloc(sizeof(char) * new_len);
	if (!new_str)
		return NULL;
	ft_strncpy(new_str, str, start);
	ft_strcpy(new_str + start, str + end);
	return (new_str);
}

char	*replace_expansion(t_data *data, t_env *envs, char *arg, int start)
{
	int	key_len;
	char	*temp_key;
	char	*value = NULL;
	char	*new_arg = NULL;
	
	key_len = find_key_len(arg, start);
	temp_key = ft_calloc(sizeof(char), (key_len + 1));
	if (!temp_key)
		return NULL;
	ft_strncpy(temp_key, arg + start + 1, key_len);
	temp_key[key_len] = '\0';
	//free_string(new_arg);
	if (find_node(envs, temp_key, data) == 1)
	{
		value = find_keys_value(envs, temp_key);
		if (value != NULL)
		{
			// this leaks no idea why
			new_arg = new_str(arg, value, start, start + key_len + 1);
		}
		else
			new_arg = remove_key(arg, start, start + key_len + 1);
	}
	else
		new_arg = remove_key(arg, start, start + key_len + 1);
	free_string(arg);
	free_string(temp_key);
	return (new_arg);
}

char	*look_if_expansions(t_data *data, t_env *envs, char *arg, int i)
{
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			arg = replace_expansion(data, envs, arg, i);
			if (arg[i + 1] == '"' || arg[i + 1] == '\'')
				return (arg);//scary
		}
		i++;
	}
	return (arg);
}
