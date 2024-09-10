/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:04:51 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/09 17:26:43 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_syntax_check(char *string)
{

	if (ft_strchr(string, '=') == NULL)
		return (1);
	if (is_char_redirect(string[0]) > 0)
	{
		return (0);	
	}
	if (ft_isalpha(string[0]) == 0)
	{
		not_perror("export", string, NOT_VALID);
		return (1);
	}
	return (0);
}
void	ft_export(t_data *data)
{
	t_tokens *tokens;
	int		i;

	i = 1;
	tokens = data->tokens;
	// if (tokens->args[1] == NULL) // maybe we don't need to handle this
	// 	ft_printf("no args beep boop declare -X\n");
	// if (data->tokens->array_count == 1)
	// 	ft_printf("print env in alphabetical order\n"); // maybe don't implement this
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
	if (export_syntax_check(arg) == 1)
		return ;
	key = ft_strtrim_front(arg, '=');
	while (env->next != NULL)
	{
		env = env->next;
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
		{
			free(env->value);
			env->value = find_value(arg);
			free(key);
			return ;
		}
	}
	insert_node(&env, key, find_value(arg));
}

char	*ft_strtrim_front(char *s1, char set)
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
