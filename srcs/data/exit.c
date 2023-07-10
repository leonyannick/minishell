/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:19:10 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/10 11:27:11 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_utils.h"

void	free_data(t_data *data)
{
	if (data->line)
		data->line = ft_free_set_null(data->line);
	if (data->env_dict)
		ft_lstclear(&data->env_dict, ft_dict_node_del);
	if (data->tokens)
		ft_lstclear(&data->tokens, token_del);
	if (data->commands)
		ft_lstclear(&data->commands, command_del);
	rl_clear_history();
}

void	exit_child(t_data *data, int exit_code)
{
	free_data(data);
	exit(exit_code);
}

void	exit_gracefully(t_data *data)
{
	printf("exit\n");
	free_data(data);
	exit(g_exit_code);
}
