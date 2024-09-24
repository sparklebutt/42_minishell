/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:33:27 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/24 15:54:54 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_interactive_mode = 1;
}

void	here_signal(int sig)
{
	g_interactive_mode = sig;
	exit(130);
}

void	handle_sigquit(int sig)
{
	// exit_code(1, 131);
	g_interactive_mode = sig;
	signal(SIGQUIT, SIG_IGN);
	write(STDOUT_FILENO, "Quit (core dumped because you asked it too)\n", 45);
}

void	signal_handler(int sig)
{
	g_interactive_mode = sig;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	// exit_code(1, 0);
}

void	set_signals(int sig)
{
	int	x;

	x = sig;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	// if (sig == 2)
	// 	exit_code(1, 130);
	// else if (sig == 0)
	// 	exit_code(1, 0);
}
