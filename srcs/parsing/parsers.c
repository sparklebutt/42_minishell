/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:17:27 by araveala          #+#    #+#             */
/*   Updated: 2024/07/04 17:43:48 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int confirm_action(int du, int si, int d, int s)
{
	if (du == 0 && si == 0)
		return (2);
	else if (s == true && d == false)
	{
		if ((si > 1 && si % 2 == 0) || du % 2 != 0 || du == 0)
			return (1);
		return (0);
	}
	else if (d == true && s == false)
	{
		if ((du > 1 && du % 2 == 0) || si % 2 == 0 || si == 0)
			return (1);
		return (0);
	}
	else if (s == true && d == true)
	{
		if (si > 1 && si % 2 == 0)
			return (0);
		return (1);
	}
	else if (s == false && d == false)
	{
		if (si > 1 && si % 2 == 0 && du < 1) // what
			return (0);
		return (1);
	}
	return (-1);
}

void	confirm_expansion(char *string, int len)
{
	bool s;
	bool d;
	int si;
	int du;
	int x;
	
	s = false;
	d = false;
	x = 0;
	si = 0;
	du = 0;
	while (x < len)
	{
		// ft_printf("lchar = %c\n",string[x]);
		if (string[x] == '\'')
		{
			len -= 1;
			si += 1;
			s = ! s;
		}
		else if (string[x] == '"')
		{
			len -= 1;
			du += 1;
			d = ! d;
		}
		x++;
	}
//	if (du == 0 && si == 0)
//		return (2);
	if (confirm_action(du, si, d, s) > 0)
	{
		ft_printf("expand true, expand and adjust quotes\n");
		//return (true)//(1);
	}
	else if (confirm_action(du, si, d, s) == 0)
	{
		ft_printf("expand false, only adjust quotes\n");
		// return (false) // (0);
	}
	// ft_printf("we have a unknown error in confirm expansion\n");
	// return (-1) // ERROR 
}

static int	isquote(char *string)
{
	int x;

	x = 0;
	while (string[x])
	{
		if (string[x] == '\'' || string[x] == '"')
			return (1);
		x++;
	}
	return (0);
}
// we could use this as a general parser and handle quotes and some syntax errors based on imidiate input and in order of importance, so far we are handling expansion and just quotes
void	expansion_parser(t_tokens *tokens)
{
	int i;
	int len;
	static char *new;
	
	i = 0;
	len = 0;
	//new = NULL;
	while (tokens->args[i])
	{
		ft_printf("TOKEN BEFORE CHANGES WITH QUOTES = %s\n", tokens->args[i]);
		len = ft_strlen(tokens->args[i]) - 1;
		if (ft_strchr(tokens->args[i], '$') != NULL)
			confirm_expansion(tokens->args[i], len);// to expand or not to expand, should also handle the expansion or we expand here based on true and false
		if (isquote(tokens->args[i]) == 1)
		{
			new = clean_quotes(tokens->args[i], count_new_len(tokens->args[i]));
			ft_printf("new created\n");
			free_string(tokens->args[i]);
//		ft_printf("token s arg freed\n\n");
			tokens->args[i] = new;
		}
		ft_printf("TOKEN AFTER quotes array update = %s \n", tokens->args[i]);
		// free_string(new);
		i++;
	}
/// testing only
	i = 0;
	while (tokens->args[i])
	{
		ft_printf("TOKEN AFTER = %s\n", tokens->args[i]);
		i++;
	}
////
}

 
/*void	mini_parser(t_tokens *tokens, int i, int x)
{
	while (tokens->args[i])
	{
		while (tokens->args[i][x])
		{
			if ()
			x++;
		}
	}
	i++;
	}*/
