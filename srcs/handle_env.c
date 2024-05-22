/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:56:15 by araveala          #+#    #+#             */
/*   Updated: 2024/05/22 13:56:51 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 #include "minishell.h"

void     lst_env(t_env *envs)
{
    extern char **environ;
    int i;
    char *test;

    i = 0;
	test = "a";
    while (environ[i] != NULL)
    {
		addnode(&envs, add_new_node(environ[i], test));
        i++;
    }
}


/*char	*lst_env()
{
    extern char **environ;
    int i;
    char **array;

    i = 0;
    while (environ[i] != NULL)
    {
        printf("whats in the environ = %s\n", environ[i]);
        printf("test = %d\n", test);
        i++;
    }
	array = ft_calloc(i, sizeof(char *));
	if (array == NULL)
		return (0);
	i = 0;
    while (environ[i] != NULL)
    {
		array[i] = environ[i];
        printf("whats in the environ = %s\n", environ[i]);
        printf("test = %d\n", test);
        i++;
    }
	
	return (array);
}*/
//array version