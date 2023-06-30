/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:02:17 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/30 13:07:47 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "../includes/types.h"

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

void	init_signals(t_data *data)
{
	data->sa.sa_handler = handle_signals;
	data->sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &data->sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}