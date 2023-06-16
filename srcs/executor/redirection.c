/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:29:38 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/16 15:03:16 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

/* 
	depending on the redirection files have to be opened with different flags.
	Depending on the redir type the function returns the appropriate flags.
	Multiple flags are connected with bitwise or.
	@argument- redir_type:	type to determine the open flags
	@return:				flags connected wit hbitwise or
 */
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

/* 
	opens the file, if exists and sets the STDIN to the opened file
	descriptor. fd is closed becuase is now set to STDIN.
	Error when file not found.
	@argument - cmd:	command to set input redir
	@retrun:			success status
 */
static int	redirect_input(t_command *cmd)
{
	cmd->inred_file.fd = open(cmd->inred_file.path,
			get_open_flags(cmd->in_redir_type),
			0777);
	if (cmd->inred_file.fd == -1)
		return (perror("Infile"), -1);
	dup2(cmd->inred_file.fd, STDIN_FILENO);
	close(cmd->inred_file.fd);
	return (0);
}

/* 
	opens every file listed after an redirection, if not existing a 
	file is created. fd is closed becuase is now set to STDOUT.
	@argument - cmd:	command to set input redir
	@retrun:			success status
 */
static int	redirect_output(t_command *cmd)
{
	t_file		*tmp_outfile;

	while (cmd->outred_file)
	{
		tmp_outfile = (t_file *)cmd->outred_file->content;
		tmp_outfile->fd = open(
				tmp_outfile->path,
				get_open_flags(cmd->out_redir_type),
				0777);
		if (tmp_outfile->fd == -1)
			perror("Outfile");
		if (cmd->outred_file->next == NULL)
			dup2(tmp_outfile->fd, STDOUT_FILENO);
		close(tmp_outfile->fd);
		cmd->outred_file = cmd->outred_file->next;
	}
	return (0);
}

int	io_redirection(int in_pipe[2], int out_pipe[2], t_list *command)
{
	t_command	*c_cmd;

	c_cmd = (t_command *)command->content;
	if (c_cmd->has_in_pipe)
		dup2(in_pipe[0], STDIN_FILENO);
	if (c_cmd->has_out_pipe)
		dup2(out_pipe[1], STDOUT_FILENO);
	if (c_cmd->in_redir_type == I_RED)
		if (redirect_input(c_cmd) == -1)
			return (-1);
	if (c_cmd->out_redir_type == O_RED || c_cmd->out_redir_type == O_RED_APP)
		if (redirect_output(c_cmd) == -1)
			return (-1);
	close_pipe_if_necessary(in_pipe);
	close_pipe_if_necessary(out_pipe);
	return (0);
}
