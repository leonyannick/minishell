/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:07:34 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/10 11:35:47 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_utils.h"

void	init_data(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	data->env_dict = ft_dict_from_strarr(envp);
	init_signals(data);
	g_exit_code = EXIT_SUCCESS;
}
