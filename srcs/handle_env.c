/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:56:15 by araveala          #+#    #+#             */
/*   Updated: 2024/05/22 16:54:50 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_key_name(char *string)
{
	char *name;
	int i;

	i = 0;
	name = NULL;
	while (string[i])
	{
		
		if (string[i] == '=')
		{
			name = ft_substr(string, 0, i);
			return (name);
		}
		i++;
	}
	printf("error in finding key name\n");
	return (0);
}

void     lst_env(t_env *envs)
{
    extern char **environ;
    int i;
    char *test;

    i = 0;
    while (environ[i] != NULL)
    {
		test = find_key_name(environ[i]);
		addnode(&envs, add_new_node(environ[i], test));
        i++;
    }
}
