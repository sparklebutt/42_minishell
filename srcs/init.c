/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:11:00 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/21 18:42:55 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init(t_data *data, char **env)
{
	int out;
	// fill minishell data struct?
	// copy env to struct
	data->prompt = "\x1b[95mminishell\033[0;37m$ ";
	out = env_init(data, env);
	return (out);
}

int	env_init(t_data *data, char **env)
{
	// understand env
	// copy env to struct
	// check if env is empty, if so, new line?
	
	(void)env;
	(void)data;
	return (0);
}