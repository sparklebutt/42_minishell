/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:28 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/18 20:16:04 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*loop_array(char **array, char *tmp, char *value)
{
	int		i;
	char	*tmp_2;

	tmp_2 = NULL;
	i = 0;
	array = ft_split(value, ':');
	if (array == NULL)
		return (NULL);
	while (array[i] != NULL)
	{
		tmp_2 = ft_strnstr(array[i], "/bin", 5);
		if (tmp_2 != NULL)
		{
			tmp = ft_strdup(tmp_2);
			break ;
		}
		i++;
	}
	free_array(array);
	return (tmp);
}

char	*env_helper(t_env *env, int i, int split_count)
{
	char	*value;
	char	*ret;
	char	*tmp;

	tmp = NULL;
	ret = NULL;
	value = find_keys_value(env, "PATH");
	if (value == NULL || ft_strlen(value) == 0)
		return (NULL);
	while (value[i++] != '\0')
		split_count++;
	tmp = loop_array(NULL, tmp, value);
	if (tmp != NULL)
		ret = ft_strdup(tmp);
	return (ret);
}

int	check_envs_ret(char *ret)
{
	if (ret == NULL || ft_strlen(ret) > 4)
	{
		if (ret != NULL && ft_strlen(ret) == 5 && ret[4] == '/')
		{
			ret = free_string(ret);
			return (0);
		}
		else
		{
			if (ret != NULL)
				ret = free_string(ret);
			return (not_perror("env", NULL, "No such file or directory\n"), 1);
		}
	}
	ret = free_string(ret);
	return (0);
}

void	ft_env(t_data *data)
{
	t_env	*env;
	char	*ret;

	env = data->env;
	ret = NULL;
	// printf("data->env->key = %s\n", data->env->key);
	// printf("data->env->next->key = %s\n", data->env->next->key);
	if (find_node(env, "PATH", data) == 1)
	{
		ret = env_helper(env, 0, 0);
		if (check_envs_ret(ret) == 1)
			return ;
	}
	else
		return (not_perror("env", NULL, "No such file or directory\n"));
	if (data->tokens->args[data->i + 1] != NULL
		&& data->tokens->args[data->i + 1][0] != '|')
	{
		if (check_dir(data->tokens->args[data->i + 1]) == 0)
			return (cmd_error("env", data->tokens->args[data->i + 1]));
	}
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
