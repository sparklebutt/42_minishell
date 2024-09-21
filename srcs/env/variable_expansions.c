/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:03:23 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 20:37:17 by vkettune         ###   ########.fr       */
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
	new_str = ft_calloc(sizeof(char), new_len + 1);
	if (!new_str)
		return (NULL);
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
		return (NULL);
	ft_strncpy(new_str, str, start);
	ft_strcpy(new_str + start, str + end);
	return (new_str);
}

char	*replace_expansion(t_data *data, t_env *envs, char *arg, int start)
{
	int		key_len;
	char	*temp_key;
	char	*value;
	char	*new_arg;

	new_arg = NULL;
	value = NULL;
	key_len = find_key_len(arg, start);
	temp_key = ft_calloc(sizeof(char), (key_len + 1));
	if (!temp_key)
		return (NULL);
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

char	*look_if_expans(t_data *data, t_env *envs, char *arg, int flag)
{
	int	i;

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
		i++;
	}
	return (arg);
}
