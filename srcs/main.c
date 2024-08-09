/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/09 09:14:21 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_data *data)
{
	char	*rl;

	while (1)
	{
		set_signals();
		rl_on_new_line();
		rl = readline(data->prompt);
		add_history(rl);
		if (rl)
    {
			collect_cmd_array(data, data->tokens, rl);
			if (handle_line(*data, data->tokens) == -1)
			{
				ft_printf("error dfghjkl\n"); // change error message
				break ;
			}
			free_array(data->tokens->args);
			free(rl);
		}
		if (!rl)
			break ;
	}
	ft_printf("exit\n");
}

int main(int argc, char **argv)
{
	static t_data data;
	static t_tokens tokens;
	static t_temps tmp;
	
	(void)argc;
	(void)argv;
	data.tokens = &tokens;
	data.tmp = &tmp;
	data.env = init(&data);
	minishell(&data);
	free_nodes(data.env);
	return (0);
}
