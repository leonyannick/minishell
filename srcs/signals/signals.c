/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:02:17 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/04 19:19:09 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "../includes/types.h"

/*
	gets executed on a SIGINT signal event. clears the buffer of readline
	writes a newline and redisplays the prompt of the
	shell.
*/
void	handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

/*
	overides the action of the signal SIGINT 'ctrl-D' with the custom handle_signal
	behaviour and ignores the SIGQUIT 'ctrl-\'.
*/
void	init_signals(t_data *data)
{
	data->sa.sa_handler = handle_signals;
	data->sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &data->sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}