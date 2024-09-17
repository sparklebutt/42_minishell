/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:03:23 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/17 13:34:03 by vkettune         ###   ########.fr       */
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
	return (len - start - 1);
}

char	*new_str(char *str, char *value, int start, size_t end)
{
	int		new_len;
	char	*new_str;
	new_len = start + ft_strlen(value) + ft_strlen(str + end) + 1;
	/*CHANGE calloc + 1*/
	// value could be an empty string and we left no room fo that
	new_str = ft_calloc(sizeof(char), new_len + 1);
	if (!new_str)
		return NULL;
	ft_strncpy(new_str, str, start);
	ft_strcpy(new_str + start, value);		
	ft_strcpy(new_str + start + ft_strlen(value), str + end);
	return (new_str);
}

char	*remove_key(char *str, int start, int end)
{
	int		new_len;
	char	*new_str;

	new_str = NULL;
	new_len = start + ft_strlen(str + end) + 1;
	new_str = ft_calloc(sizeof(char), new_len + 1);
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
	if (find_node(envs, temp_key, data) == 1)
	{
		value = find_keys_value(envs, temp_key);
		if (value != NULL)
			new_arg = new_str(arg, value, start, start + key_len + 1);
		else
			new_arg = remove_key(arg, start, start + key_len + 1);
	}
	else
		new_arg = remove_key(arg, start, start + key_len + 1);
	arg = free_string(arg);
	temp_key = free_string(temp_key);
	return (new_arg);
}

char *replace_exitcode(char *arg, int start)
{
	char	*value = NULL;
	char	*new_arg = NULL;
	
	value = ft_itoa(exit_code(0, 0));
	new_arg = new_str(arg, value, start, start + 1 + 1);
	value = free_string(value); // new free by vilja, was leaking
	arg = free_string(arg);
	return (new_arg);
}

char	*look_if_expansions(t_data *data, t_env *envs, char *arg, int flag)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			if (flag == 1)
				return (arg);
			if (arg[i + 1] == '?')
				arg = replace_exitcode(arg, i);
			else
				arg = replace_expansion(data, envs, arg, i);
			if (arg[i] != '\0' && (arg[i + 1] == '"' || arg[i + 1] == '\''))
				return (arg);
			if (arg[i] == '\0')
				 return (arg);
		}
		// if (arg[0] == '~' && ft_strlen(arg) == 1)
		// {
		// 	arg = free_string(arg); // cause we don't free arg in the fucntion below, vilja
		// 	arg = replace_squiggly_line(data, envs);
		// }
		i++;
	}
	return (arg);
}
