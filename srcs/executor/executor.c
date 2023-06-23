/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:58:03 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/23 09:59:41 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

/* 
	Like bash, every heredoc of every pipe is read at the beginning before forking.
	then forks a child prcess for every command. if returnes id is 0, we are in the 
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
			if (io_redirection(in_pipe, out_pipe, cmd_head->content) == -1)
				return (-1);
			if (command->type == PATH)
				return (execute_path_cmd(data, command));
			if (command->type == BUILTIN)
				return (exeute_builtin_cmd(data, command, -1));
		}
		close_pipe(in_pipe);
		cmd_head = cmd_head->next;
		i++;
	}
	close_pipe(out_pipe);
	return (0);
}

/*
	If there is an unpiped built in, it has to be executed in the main process.
	Therefore the stdout of the main process has to be redirected befor execution
	and set back after execution, because minishell will continue execution
	and needs to read and write to normal STDIO.
*/
int	execute_builtin_inplace(t_data *data, t_command *command)
{
		int	old_stdin;
		int	old_stdout;
		int	exec_ret;

		old_stdin = dup(STDIN_FILENO);
		old_stdout = dup(STDOUT_FILENO);
		io_redirection(NULL, NULL, command);
		exec_ret = exeute_builtin_cmd(data, command, 0);
		dup2(old_stdin, STDIN_FILENO);
		close(old_stdin);
		dup2(old_stdout, STDOUT_FILENO);
		close(old_stdout);
		return (exec_ret);
}

/* 
	If a singele builtin is executed it is done inplace (in the main process).
	In a piped pipeline EVERY command is forked.
	@argument - data:	data object containing envp and commands linked list
	@return:			success status
 */
int	execute(t_data *data)
{
	int	*pids;
	int	i;
	int	cmd_count;
	t_command	*command;

	i = 0;
	if (!data->commands)
		return (0);
	command = (t_command *)data->commands->content;
	read_heredocs(data->commands);
	cmd_count = ft_lstsize(data->commands);
	if (cmd_count == 1 && command->type == BUILTIN)
		return (execute_builtin_inplace(data, command));
	pids = malloc(cmd_count * sizeof(int));
	if (children(pids, data) == -1)
		return (-1);
	while (i < cmd_count)
		waitpid(pids[i++], NULL, 0);
	pids = ft_free_set_null(pids);
	return (0);
}
