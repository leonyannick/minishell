/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:29:38 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/13 14:03:47 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "executor_utils.h"

static int	get_open_flags(e_token_types redir_type)
{
	if (redir_type == I_RED)
		return (O_RDONLY);
	if (redir_type == O_RED)
		return (O_TRUNC | O_RDWR | O_CREAT);
	if (redir_type == O_RED_APP)
		return (O_CREAT | O_APPEND | O_RDWR);
	return (0);
}

int	io_redirection(t_list *command, int **pipes, int index, t_data *data)
{
	t_command	*c_cmd;
	t_file		*tmp_outfile;

	c_cmd = (t_command *)command->content;
	if (c_cmd->has_in_pipe)
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (c_cmd->has_out_pipe)
		dup2(pipes[index][1], STDOUT_FILENO);
	if (c_cmd->in_redir_type == I_RED)
	{
		c_cmd->inred_file.fd = open(c_cmd->inred_file.path, get_open_flags(c_cmd->in_redir_type), 0777);
		if (c_cmd->inred_file.fd == -1)
			return (perror("Infile"), -1); //TODO: cleanup
		dup2(c_cmd->inred_file.fd, STDIN_FILENO);
		close(c_cmd->inred_file.fd);
	} 
	if (c_cmd->out_redir_type == O_RED || c_cmd->out_redir_type == O_RED_APP)
	{
		while (c_cmd->outred_file)
		{
			tmp_outfile = (t_file *)c_cmd->outred_file->content;
			tmp_outfile->fd = open(tmp_outfile->path, get_open_flags(c_cmd->out_redir_type), 0777);
			if (tmp_outfile->fd == -1)
				perror("Outfile"); //TODO: cleanup
			if (c_cmd->outred_file->next == NULL)
				dup2(tmp_outfile->fd, STDOUT_FILENO);
			close(tmp_outfile->fd);
			c_cmd->outred_file = c_cmd->outred_file->next;
		}
	}
	close_pipe_fd(pipes, data);
	return (0);
}
