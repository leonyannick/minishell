/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:29:38 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/27 17:10:25 by aehrlich         ###   ########.fr       */
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
static int	get_flags(e_token_types redir_type)
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
	t_file		*file;
	t_list		*file_head;

	file_head = cmd->inred_file;
	while (file_head)
	{
		file = (t_file *)file_head->content;
		file->fd = open(file->path, get_flags(cmd->in_redir_type), 0777);
		if (file->open_mode == I_RED && file->fd == -1)
			perror("Infile");
		if (file_head->next == NULL)
		{
			file->fd = open(file->path, O_RDONLY, 0777);
			if (file->fd == -1)
				return (-1);
			dup2(file->fd, STDIN_FILENO);
		}
		if (file->fd != -1)
			close(file->fd);
		file_head = file_head->next;
	}
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
	t_file		*file;
	t_list		*file_head;

	file_head = cmd->outred_file;
	while (file_head)
	{
		file = (t_file *)file_head->content;
		file->fd = open(file->path, get_flags(cmd->out_redir_type), 0777);
		if (file->fd == -1)
			perror("Outfile");
		if (file_head->next == NULL)
			dup2(file->fd, STDOUT_FILENO);
		close(file->fd);
		file_head = file_head->next;
	}
	return (0);
}

int	io_redirection(int in_pipe[2], int out_pipe[2], t_command *command)
{
	if (command->has_in_pipe && in_pipe)
		dup2(in_pipe[0], STDIN_FILENO);
	if (command->has_out_pipe && out_pipe)
		dup2(out_pipe[1], STDOUT_FILENO);
	if (command->in_redir_type == I_RED || command->in_redir_type == I_RED_HD)
		if (redirect_input(command) == -1)
			return (-1);
	if (command->out_redir_type == O_RED
		|| command->out_redir_type == O_RED_APP)
		if (redirect_output(command) == -1)
			return (-1);
	close_pipe(in_pipe);
	close_pipe(out_pipe);
	return (0);
}
