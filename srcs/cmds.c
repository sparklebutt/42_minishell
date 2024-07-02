/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:28:04 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/22 09:36:50 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd(t_data *data)
{
	(void)data;
	return (0);
}

int cd(t_data *data, char *path)
{
	(void)data;
	(void)path;
	return (0);
}

int echo(t_data *data, char *str)
{
	(void)data;
	(void)str;
	return (0);
}

int env(t_data *data)
{
	(void)data;
	return (0);
}	

int export(t_data *data)
{
	(void)data;
	return (0);
}

int unset(t_data *data)
{
	(void)data;
	return (0);
}

int ft_exit(t_data *data)
{
	(void)data;
	return (0);
}
