/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:59:05 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/18 10:07:58 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

void	free_data(t_data *data);
void	exit_child(t_data *data, int exit_code);
void	exit_gracefully(t_data *data);
void	init_data(t_data *data, char **envp);

#endif
