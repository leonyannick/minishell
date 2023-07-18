/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:12:17 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/18 16:43:57 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

/*
	reads the STDIO into the opened unique .herdoc_IDX
	in /tmp until a the limiter is entered.
*/
static int	ft_read_heredoc(int fd, char *lim)
{
	char	*read;

	read = readline("> ");
	if (!read)
		ft_fd_printf(STDERR_FILENO, 
			"warning: heredoc delimited by EOF (wanted '%s')\n", lim);
	while (read && (ft_strlen(read) != ft_strlen(lim)
			|| ft_strncmp(read, lim, ft_strlen(lim))))
	{
		write(fd, read, ft_strlen(read));
		write(fd, "\n", 1);
		read = ft_free_set_null(read);
		read = readline("> ");
		if (!read)
			ft_fd_printf(STDERR_FILENO,
				"warning: heredoc delimited by EOF (wanted '%s')\n", lim);
	}
	read = ft_free_set_null(read);
	close(fd);
	return (0);
}

/*
	herdocs can appear also in pipes. Therefor, like bash, is
	reads all heredocs at the beginning even if a cmd is not valid.
	@return: 0 on success, -1 on failure
*/
int	read_heredocs(t_list *cmd_head)
{
	t_file		*in_file;
	t_list		*file_head;
	t_command	*cmd;

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
				if (in_file->fd == -1)
					return (-1);
				ft_read_heredoc(in_file->fd, in_file->herdoc_lim);
			}
			file_head = file_head->next;
		}
		cmd_head = cmd_head->next;
	}
	return (0);
}
