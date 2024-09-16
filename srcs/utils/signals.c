/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:33:27 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/16 07:13:12 by araveala         ###   ########.fr       */
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
//dont need this because we already handle it as should
void	handle_cc()
{
	//write(STDOUT_FILENO, "\n", 1);
	signal(SIGINT, SIG_DFL);
	//raise(SIGINT);
	kill(g_interactive_mode, SIGINT);	
}
void	handle_sigquit()
{

	write(STDOUT_FILENO, "Quit (core dumped because you asked it too)\n", 45);
	//write(STDOUT_FILENO, "\n", 1);
    signal(SIGQUIT, SIG_DFL);
	kill(g_interactive_mode, SIGQUIT);
}
void reset_signals()
{
	signal(SIGINT, handle_cc);
    signal(SIGQUIT, handle_sigquit);
	//while (1)
	//	pause(); // just  have to wait for the signals so all can happen in right order
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		//printf("what teh jizz is it = %d\n", g_interactive_mode);
		if (g_interactive_mode == 1)
		{
			ft_printf("\n");
			
			rl_replace_line("", 0); //not sure this doe anything
			
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
