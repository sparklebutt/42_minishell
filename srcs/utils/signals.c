/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:33:27 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 21:21:15 by vkettune         ###   ########.fr       */
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
	struct sigaction	sa;

	g_interactive_mode = sig;
	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
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
	int	x;

	x = sig;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

// void	here_signal(int sig)
// {
// 	g_interactive_mode = sig;
// }

// void	handle_sigquit(int signo)
// {
// 	g_interactive_mode = signo;
// 	signal(SIGQUIT, SIG_IGN);
// 	write(STDOUT_FILENO, "Quit (core dumped because you asked it too)\n", 45);
// }

// void	signal_handler(int signo)
// {
// 	g_interactive_mode = signo;
// 	rl_replace_line("", 0);
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	set_signals()
// {
// 	signal(SIGINT, signal_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }
