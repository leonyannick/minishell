/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:07:34 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/07 11:01:38 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/data_init.h"

void	init_data(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	data->env_dict = ft_dict_from_strarr(envp);
	init_signals(data);
	g_exit_code = EXIT_SUCCESS;
}
