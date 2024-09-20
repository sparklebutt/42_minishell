/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:33:27 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/20 10:00:15 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signals(void)
{
	struct sigaction	sig_act;

	sigemptyset(&sig_act.sa_mask);
	sig_act.sa_flags = SA_RESTART;
	sig_act.sa_handler = &signal_handler;
	sigaction(SIGINT, &sig_act, NULL);
	sig_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_act, NULL);
}

/*set to default*/
void	handle_cc(int signo)
{
	(void)signo;
	signal(SIGINT, SIG_DFL);
	kill(g_interactive_mode, SIGINT);
}

void	handle_sigquit(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "Quit (core dumped because you asked it too)\n", 46);
	signal(SIGQUIT, SIG_DFL);
	kill(g_interactive_mode, SIGQUIT);
}

void	reset_signals(int signo)
{
	(void)signo;
	signal(SIGINT, handle_cc);
	signal(SIGQUIT, handle_sigquit);
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (g_interactive_mode == 1)
		{
			ft_printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
