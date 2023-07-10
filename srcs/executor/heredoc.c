/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:12:17 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/10 11:55:34 by aehrlich         ###   ########.fr       */
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

	write(STDOUT_FILENO, "> ", 2);
	read = get_next_line(STDIN_FILENO);
	lim = ft_strjoin(lim, "\n");
	while (ft_strncmp(read, lim, ft_strlen(lim)) != 0)
	{
		write(STDOUT_FILENO, "> ", 2);
		write(fd, read, ft_strlen(read));
		read = ft_free_set_null(read);
		read = get_next_line(STDIN_FILENO);
	}
	read = ft_free_set_null(read);
	lim = ft_free_set_null(lim);
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
				if (!in_file->fd)
					return (-1);
				ft_read_heredoc(in_file->fd, in_file->herdoc_lim);
			}
			file_head = file_head->next;
		}
		cmd_head = cmd_head->next;
	}
	return (0);
}
