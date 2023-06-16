/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:58:03 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/16 13:28:52 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

/* 
	forks a child prcess for every command. if returnes id is 0, we are in the 
	forked child and can set up the command execution. The output gets redirected,
	the pipes get set up and based on the cmd type the command gets executed either
	in the shell or via exec call.
	@argument - pipes:	pipes to populate with filedescriptors
	@argument - pids:	child process ids to wait for
	@data:				main data object
	@return:			sucess status
 */
static int	children(int *pids, t_data *data)
{
	int			i;
	int			in_pipe[2];
	int			out_pipe[2];
	t_list		*cmd_head;
	t_command	*command;

	i = 0;
	init_pipes(in_pipe, out_pipe);
	cmd_head = data->commands;
	while (cmd_head)
	{
		command = (t_command *)cmd_head->content;
		if (command->has_in_pipe)
			ft_memcpy(in_pipe, out_pipe, 2 * sizeof(int));
		if (command->has_out_pipe)
			pipe(out_pipe);
		pids[i] = fork();
		if (pids[i] == -1)
			return (-1);
		if (pids[i] == 0)
		{
			io_redirection(in_pipe, out_pipe, cmd_head);
			if (command->type == PATH)
				return (execute_path_cmd(data, command));
		}
		close_pipe_if_necessary(in_pipe);
		cmd_head = cmd_head->next;
		i++;
	}
	close_pipe_if_necessary(out_pipe);
	return (0);
}

/* 
	creates a childprocess for every command, sets up the pipes
	and redirections and executes the child commands processes
	(BUILTIN and PATH) and waits for them to be finished.
	@argument - data:	data object containing envp and commands linked list
	@return:			success status
 */
int	execute(t_data *data)
{
	int	*pids;
	int	i;
	int	cmd_count;

	i = 0;
	if (!data->commands)
		return (1);
	cmd_count = ft_lstsize(data->commands);
	pids = malloc(cmd_count * sizeof(int));
	if (children(pids, data) == -1)
		return (-1);
	while (i < cmd_count)
		waitpid(pids[i++], NULL, 0);
	free(pids);
	return (0);
}
