/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:33:27 by vkettune          #+#    #+#             */
/*   Updated: 2025/07/09 16:06:39 by araveala         ###   ########.fr       */
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
}

void	set_signals(int sig)
{
	(void) sig;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
