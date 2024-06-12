/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:04:51 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/10 18:24:40 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *data)
{
	t_env	*env;
	t_tokens *tokens;
	int		i;

	i = 1;
	tokens = data->tokens;
	env = data->env;
	if (tokens->args[1] == NULL)
		ft_printf("no args\n");
	if (data->tokens->array_count == 1)
		ft_printf("print env in alphabetical order\n");
	while (i < data->tokens->array_count)
	{
		handle_arg(data, i, data->tokens);
		i++;
	}
}

void handle_arg(t_data *data, int arg_i, t_tokens *tokens)
{
	char	*arg;
	t_env	*env;
	char	*key;
	
	env = data->env;
	arg = tokens->args[arg_i];
	if (ft_strchr(arg, '=') == NULL)
		return ; // bash does not give an error message here
	check_char(data, arg_i, 0);
	key = ft_strtrim_front(arg, '=');
	while (env->next != NULL)
	{
		env = env->next;
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
		{
			// ft_printf("key exists\n");
			free(env->value);
			env->value = find_value(arg);
			free(key);
			return ;
		}
	}
	// ft_printf("key does not exist\n");
	insert_node(&env, key, find_value(arg));
}

char	*ft_strtrim_front(char *s1, char set) // move somewhere else or rewrite
{
	int		i;
	char	*trimmed_str;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(&s1[i], set))
	{
		if (s1[i] == '\0')
				return (NULL);
		i++;
	}
	trimmed_str = ft_substr(s1, 0, i - 1);
	if (trimmed_str == NULL)
		return (NULL);
	return (trimmed_str);
}
