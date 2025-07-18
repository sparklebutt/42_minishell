/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:04:51 by vkettune          #+#    #+#             */
/*   Updated: 2025/07/09 16:00:52 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_syntax_check(char *string)
{
	int	i;

	if (string == NULL)
		return (0);
	i = ft_strlen(string);
	if (ft_isalpha(string[0]) == 0)
		return (not_perror("export", string, NOT_VALID), 1);
	if (ft_strchr(string, '=') == NULL)
	{
		if (ft_isalpha(string[i - 1]) == 0 && ft_isalnum(string[i - 1]) == 0)
			return (not_perror("export", string, NOT_VALID), 1);
		return (1);
	}
	i = 0;
	while (string[i] && string[i] != '=')
		i++;
	if (ft_isalpha(string[i - 1]) == 0 && ft_isalnum(string[i - 1]) == 0)
		return (not_perror("export", string, NOT_VALID), 1);
	return (0);
}

t_env	*sort_env(t_env *lst)
{
	t_env	*start;
	char	*new_key;
	char	*new_value;

	start = lst;
	while (lst != NULL && lst->next != NULL)
	{
		if (compare_str(lst->key, lst->next->key) == 0)
		{
			new_key = lst->key;
			lst->key = lst->next->key;
			lst->next->key = new_key;
			new_value = lst->value;
			lst->value = lst->next->value;
			lst->next->value = new_value;
			lst = start;
		}
		else
			lst = lst->next;
	}
	return (start);
}

void	export_alphabetical(t_data *data)
{
	t_env	*temp_env;
	t_env	*fuck_off;
	t_env	*huh;

	fuck_off = data->env;
	huh = NULL;
	while (fuck_off != NULL)
	{
		insert_node(&huh, ft_strdup(fuck_off->key), ft_strdup(fuck_off->value));
		fuck_off = fuck_off->next;
	}
	temp_env = sort_env(huh);
	while (temp_env != NULL)
	{
		printf("declare -x %s=\"%s\"\n", temp_env->key, temp_env->value);
		temp_env = temp_env->next;
	}
	free_nodes(huh);
}

void	ft_export(t_data *data)
{
	int			i;

	i = 1;
	if (data->tokens->array_count == 1)
		export_alphabetical(data);
	else
	{
		while (i < data->tokens->array_count)
		{
			handle_arg(data, i, data->tokens);
			i++;
		}
	}
}

void	handle_arg(t_data *data, int arg_i, t_tokens *tokens)
{
	char	*arg;
	t_env	*env;
	char	*key;
	char	*value;

	env = data->env;
	arg = tokens->args[arg_i];
	if (export_syntax_check(arg) == 1)
		return ;
	key = ft_strtrim_front(arg, '=');
	while (env->next != NULL)
	{
		env = env->next;
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
		{
			env->value = free_string(env->value);
			env->value = find_value(arg);
			key = free_string(key);
			return ;
		}
	}
	value = find_value(arg);
	insert_node(&env, key, value);
}
