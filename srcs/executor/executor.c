/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:58:03 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/12 17:56:58 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

static void	execute_children(int *in_pipe, int *out_pipe,
	t_command *command, t_data *data)
{
	if (io_redirection(in_pipe, out_pipe, command) == -1)
		exit_child(data, EXIT_FAILURE);
	if (command->type == PATH && command->arguments)
		execute_path_cmd(data, command);
	else if (command->type == BUILTIN && command->arguments)
		exit_child(data, execute_builtin_cmd(data, command));
	exit_child(data, EXIT_FAILURE);
}

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
static void	children(int *pids, t_data *data)
{
	int			i;
	int			in_pipe[2];
	int			out_pipe[2];
	t_list		*cmd_head;
	t_command	*command;

	i = 0;
	cmd_head = data->commands;
	init_pipes(in_pipe, out_pipe);
	while (cmd_head)
	{
		command = (t_command *)cmd_head->content;
		set_pipes(command, in_pipe, out_pipe);
		pids[i] = fork();
		if (pids[i] == -1)
			exit_child(data, EXIT_FAILURE);
		if (pids[i++] == 0)
		{
			free(pids);
			execute_children(in_pipe, out_pipe, command, data);
		}
		close_pipe(in_pipe);
		cmd_head = cmd_head->next;
	}
	close_pipe(out_pipe);
}

/*
	If there is an unpiped built in, it has to be executed in the main process.
	Therefore the stdout of the main process has to be redirected befor execution
	and set back after execution, because minishell will continue execution
	and needs to read and write to normal STDIO.
*/
static int	execute_builtin_inplace(t_data *data, t_command *command)
{
	int	old_stdin;
	int	old_stdout;
	int	exit_code;

	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	io_redirection(NULL, NULL, command);
	exit_code = execute_builtin_cmd(data, command);
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);
	return (exit_code);
}

/*
	waits for all the forked children and evaluates the 
	exitcodes of the executed child process and stores it in
	the global exit code.
	@param:	cmd_count:	amount of commands to wait for
			pids:		process ids of childs to wait for
*/
static int	parent_wait(int cmd_count, int *pids)
{
	int	i;
	int	wstatus;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i++], &wstatus, 0);
		if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			exit_code = 128 + WTERMSIG(wstatus);
	}
	return (exit_code);
}

/* 
	If a singele builtin is executed it is done inplace (in the main process).
	In a piped pipeline EVERY command is forked. If the minishell is called
	inside the minishell, the signals send to the parent has to be ignored,
	for the time of executing the child minishell. After finishing the child
	(waiting for its execution), the parent is set to handle the signals again.
	@argument - data:	data object containing envp and commands linked list
	@return:			success status
 */
int	execute(t_data *data)
{
	int			*pids;
	int			cmd_count;
	t_command	*command;
	int			exit_code;

	command = (t_command *)data->commands->content;
	read_heredocs(data->commands);
	cmd_count = ft_lstsize(data->commands);
	if (cmd_count == 1 && command->type == BUILTIN)
		return (execute_builtin_inplace(data, command));
	pids = malloc(cmd_count * sizeof(int));
	children(pids, data);
	if (is_minishell_called(data, command))
		init_signals(data, ignore_sigint);
	exit_code = parent_wait(cmd_count, pids);
	pids = ft_free_set_null(pids);
	init_signals(data, handle_signals);
	return (exit_code);
}
