/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:02:17 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/10 17:58:37 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
 #include <sys/ioctl.h>
#include "../includes/types.h"


extern int	g_exit_code;
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
		g_exit_code = 130;
	}
}

void	ignore_sigint(int signal)
{
	if (signal == SIGINT)
		return ;
}

void	change_handler(t_data *data)
{
	if (data->sa.sa_handler == handle_signals)
		data->sa.sa_handler = ignore_sigint;
	else
		data->sa.sa_handler = handle_signals;
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