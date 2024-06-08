/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/08 19:38:50 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)//, char **env)
{
	char	*rl;
	static t_data data;
	static t_tokens tokens;
	static t_temps tmp;

	(void)argc;
	(void)argv;
	data.tokens = &tokens;
	data.tmp = &tmp;
	data.env = init(&data);
	while (1)
	{
		set_signals();
		rl_on_new_line();
		rl = readline(data.prompt);
		add_history(rl);
		if (rl)
		{
			collect_cmd_array(&tokens, rl);
			if (tokens.args[0] == NULL)
				break ;
			// example of execve() usage in check_passage
			if (handle_line(data, *data.env, &tokens, rl) == -1)
			{
				ft_printf("error\n");
				break ;
			}
			free_array(tokens.args);
			free(rl);
		}
		if (!rl)
			break ;
	}
	free_nodes(data.env);
	return (0);
}
