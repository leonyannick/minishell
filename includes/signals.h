/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:32:52 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/12 17:14:23 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "types.h"

void	handle_signals(int signal);
void	init_signals(t_data *data, void (*handle)(int));
void	ignore_sigint(int signal);
void	handle_signals_2(int signal);

#endif