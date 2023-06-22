/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:33:20 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/22 17:48:34 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

static void	file_del(void *arg)
{
	t_file	*file;

	file = (t_file *)arg;
	file->path = ft_free_set_null(file->path);
	file->herdoc_lim = ft_free_set_null(file->herdoc_lim);
	file = ft_free_set_null(file);
}

void	command_del(void *arg)
{
	t_command	*command;

	command = (t_command *)arg;
	ft_lstclear(&command->arguments, free);
	ft_lstclear(&command->outred_file, file_del);
	ft_lstclear(&command->inred_file, file_del);
	command = ft_free_set_null(command);
}
