/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:33:20 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/14 19:00:26 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

static void	file_del(void *arg)
{
	t_file *file;
	
	file = (t_file *)arg;
	ft_free_set_null(file->path);
	ft_free_set_null(file);
}

void	command_del(void *arg)
{
	t_command *command;

	command = (t_command *)arg;
	ft_lstclear(&command->arguments, free);
	ft_free_set_null(command->inred_file.path);
	ft_lstclear(&command->outred_file, file_del);
	free(command);
}
