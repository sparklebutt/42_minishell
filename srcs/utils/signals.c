/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:33:27 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/09 09:28:51 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signals(void)
{
	struct sigaction	sig_act;

	sigemptyset(&sig_act.sa_mask);
		// clearing previously set signals.
		// although im not sure if any are actualy set at this point
	sig_act.sa_flags = SA_RESTART;
		// this comes recomended although for
		// signal other than SIGCHLD has no effect apparently
	sig_act.sa_handler = &signal_handler;
	sigaction(SIGINT, &sig_act, NULL);
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("testetstetstets\n");
		rl_on_new_line();
		rl_redisplay();
	}
}
