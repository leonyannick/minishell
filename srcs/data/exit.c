/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:19:10 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/17 09:21:40 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_utils.h"

/**
 * return memory of:
 * -line from readline
 * -dictionary of environment variables
 * -tokens from lexer
 * -command list from executor
 * also clear history from readline
*/
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

/**
 * call this function when an error inside a child occurrs
*/
void	exit_child(t_data *data, int exit_code)
{
	free_data(data);
	exit(exit_code);
}

/**
 * call this function whenever the minishell is quit by either:
 * -pressing ctrl + d
 * -calling the exit function
*/
void	exit_gracefully(t_data *data)
{
	printf("exit\n");
	free_data(data);
	exit(g_exit_code);
}
