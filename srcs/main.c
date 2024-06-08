/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/08 17:24:06 by vkettune         ###   ########.fr       */
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
	data.env = lst_env();
	data.tmp = &tmp;
	ms_init(&data); // if we want to error handle the return value of ms_init, we can
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
