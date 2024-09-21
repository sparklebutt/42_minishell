/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:33:27 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 17:59:24 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_signal(int sig)
{
	g_interactive_mode = sig;
}

void	handle_sigquit(int signo)
{
	g_interactive_mode = signo;
	signal(SIGQUIT, SIG_IGN);
	write(STDOUT_FILENO, "Quit (core dumped because you asked it too)\n", 45);
}

void	signal_handler(int signo)
{
	g_interactive_mode = signo;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
