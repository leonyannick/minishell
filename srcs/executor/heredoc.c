/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:12:17 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/22 16:35:01 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

static int ft_read_heredoc(int fd, char *lim)
{
	char *read;

	write(STDOUT_FILENO, "> ", 2);
	read = get_next_line(STDIN_FILENO);
	while (ft_strncmp(read, lim, ft_strlen(ft_strtrim(read, "\n"))) != 0)
	{
		write(STDOUT_FILENO, "> ", 2);
		write(fd, read, ft_strlen(read));
		read = ft_free_set_null(read);
		read = get_next_line(STDIN_FILENO);
	}
	read = ft_free_set_null(read);
	close(fd);
	return (0);
}

int read_heredocs(t_list *cmd_head)
{
	t_file *in_file;
	t_list *file_head;
	t_command *cmd;

	while (cmd_head)
	{
		cmd = (t_command *)cmd_head->content;
		file_head = cmd->inred_file;
		while (file_head)
		{
			in_file = (t_file *)file_head->content;
			if (in_file->open_mode == I_RED_HD)
			{
				in_file->fd = open(in_file->path, O_CREAT | O_RDWR, 0777);
				ft_read_heredoc(in_file->fd, in_file->herdoc_lim);
			}
			file_head = file_head->next;
		}
		cmd_head = cmd_head->next;
	}
	return (0);
}

int delete_heredocs(t_data *data)
{
	t_list *file_head;
	t_list *command_head;
	t_file *tmp_file;

	command_head = data->commands;
	while (command_head)
	{
		file_head = ((t_command *)command_head->content)->inred_file;
		while (file_head)
		{
			tmp_file = (t_file *)file_head->content;
			if (tmp_file->open_mode == I_RED_HD)
				unlink(tmp_file->path);
			file_head = file_head->next;
		}
		command_head = command_head->next;
	}
	return (0);
}
