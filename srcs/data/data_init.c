/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:07:34 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/17 09:24:01 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_utils.h"

/**
 * to avoid error memset all stack allocated memory of data struct to zero
 * convert str arr envp to a dictionary (for easier usage in builtin functions)
 * initialize the signals and signalhandlers
 * set the exit code to 0 (EXIT_SUCCESS)
 * set flag is_minishell to false
*/
void	init_data(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	data->env_dict = ft_dict_from_strarr(envp);
	init_signals(data, handle_signals);
	g_exit_code = EXIT_SUCCESS;
	data->is_child_minishell = false;
}
