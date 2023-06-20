/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:12:17 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/20 09:39:44 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

static int	ft_read_heredoc(int fd, char *lim)
{
	char	*read;

	write(STDOUT_FILENO, "> ", 2);
	read = get_next_line(STDIN_FILENO);
	while (ft_strncmp(read, lim, ft_strlen(lim)) != 0)
	{
		write(STDOUT_FILENO, "> ", 2);
		write(fd, read, ft_strlen(read));
		free(read);
		read = get_next_line(STDIN_FILENO);
	}
	free(read);
	close(fd);
	return (0);
}

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
				ft_read_heredoc(in_file->fd, in_file->herdoc_lim);
			}
			file_head = file_head->next;
		}
		cmd_head = cmd_head->next;
	}
	return (0);
}

int	delete_heredocs(t_data *data)
{
	t_list		*file_head;
	t_list		*command_head;
	t_file		*tmp_file;
	t_command	*del_commad;
	bool		create_cmd_list;
	int			pid;

	del_commad = NULL;
	create_cmd_list = true;
	command_head = data->commands;
	while (command_head)
	{
		file_head = ((t_command *)command_head->content)->inred_file;
		while (file_head)
		{
			tmp_file = (t_file *)file_head->content;
			if (tmp_file->open_mode == I_RED_HD)
			{
				if (create_cmd_list)
				{
					del_commad = malloc(sizeof(t_command));
					ft_lstadd_back(&del_commad->arguments, ft_lstnew((void *)"rm"));
					create_cmd_list = false;
				}
				ft_lstadd_back(&del_commad->arguments, ft_lstnew((void *)tmp_file->path));
			}
			file_head = file_head->next;
		}
		command_head = command_head->next;
	}
	if (del_commad)
	{
		pid = fork();
		if (pid == 0)
			execute_path_cmd(data, del_commad);
		else
			waitpid(pid, NULL, 0);
	}
	return(0);
}