/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:04:51 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/11 11:28:31 by araveala         ###   ########.fr       */
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

int compare_str(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] == str2[i])
		i++;	
	if (str1[i] > str2[i])
		return (1);
	return (0);
}

t_env *sort_env(t_env *lst)
{
	t_env *start;
	char *new_key;
	char *new_value;

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

void export_alphabetical(t_data *data)
{
	t_env *temp_env;
	t_env *fuck_off;
	t_env *huh;

	fuck_off = data->env;
	huh = NULL;
	while (fuck_off != NULL)
	{
		insert_node(&huh, fuck_off->key, fuck_off->value);
		fuck_off = fuck_off->next;
	}
	temp_env = sort_env(huh);
	while (temp_env != NULL)
	{
		printf("declare -x %s=\"%s\"\n", temp_env->key, temp_env->value);
		temp_env = temp_env->next;
	}
}

void	ft_export(t_data *data)
{
	t_tokens *tokens;
	int		i;

	i = 1;

	tokens = data->tokens;
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

void handle_arg(t_data *data, int arg_i, t_tokens *tokens)
{
	char	*arg;
	t_env	*env;
	char	*key;
	char	*value;
	
	env = data->env;
	arg = tokens->args[arg_i];
	// args is correct
	//printf("\t\tlets check that token right = %s len = %zu\n", tokens->args[arg_i], ft_strlen(tokens->args[arg_i]));
	if (export_syntax_check(arg) == 1)
		return ;
	key = ft_strtrim_front(arg, '=');
	//printf("\t\tcomp key = %s len = %zu\n", key, ft_strlen(key));
	// key is not the issue
	while (env->next != NULL)
	{
		env = env->next;
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
		{
			free_string(env->value);
			env->value = find_value(arg);
			free_string(key);
			return ;
		}
	}
	value = find_value(arg);
	/*CHANGE value=null*/
	// adding null as value causes a problem i think because its not read as an empty string
	// removing it we loose 1 less block and some leaks
	//if (!value[0])
	//	value = NULL;
	insert_node(&env, key, value);
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
