/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:28 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/12 14:05:58 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *env_helper(t_env *env, int i, int split_count)
{
	char **array;
	char *value;
	char *ret;

	value = find_keys_value(env, "PATH");
	if (value == NULL || ft_strlen(value) == 0)
		return (NULL);
	while (value[i++] != '\0')
		split_count++;
	array = ft_calloc(sizeof(char *), split_count + 1);
	if (array == NULL)
		return (NULL);
	array = ft_split(value, ':');
	i = 0;
	while (array[i] != NULL)
	{
		ret = ft_strnstr(array[i], "/bin", 5);
		if (ret != NULL)
			break ;
		i++;
	}
	return (ret);
}

int check_envs_ret(char *ret)
{
	if (ret == NULL || ft_strlen(ret) > 4)
	{
		if (ret != NULL && ft_strlen(ret) == 5 && ret[4] == '/')
			ret[4] = '/';
		else
			return (not_perror("env", NULL, "No such file or directory\n"), 1);	
	}
	return (0);
}

void	ft_env(t_data *data)
{
	t_env	*env;
	char *ret;

	env = data->env;
	ret = NULL;
	if (find_node(env, "PATH", data) >= 1)
	{
		ret = env_helper(env, 0, 0);
		if (check_envs_ret(ret) == 1)
			return ;
	}
	else
		return (not_perror("env", NULL, "No such file or directory\n"));	
	if (data->tokens->args[data->i + 1] != NULL && data->tokens->args[data->i + 1][0] != '|')
	{ 
		if (check_dir(data->tokens->args[data->i + 1]) == 0) {
			cmd_error("env", data->tokens->args[data->i + 1]);
			return ;
		}
	}
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
