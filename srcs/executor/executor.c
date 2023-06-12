/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:58:03 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/12 15:46:01 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

int	**ft_create_pipes(t_list *commands)
{
	int	**pipes;
	int	pipe_count;
	int	i;

	i = 0;
	if (!commands)
		return (NULL);
	pipe_count = ft_lstsize(commands) - 1;
	pipes = malloc(pipe_count *  sizeof(int *));
	if (!pipes)
		return (NULL);
	while (i < pipe_count)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i])
			return (printf("NULL:-)\n"), NULL); //TODO: Free **pipes
		if (pipe(pipes[i]) == -1)
			return (NULL);
		i++;
	}
	return (pipes);
}

int	io_redirection(t_list *command, int **pipes, int index)
{
	t_command *casted_cmd;

	casted_cmd = (t_command *)command->content;
	if (casted_cmd->has_in_pipe)
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (casted_cmd->has_out_pipe)
		dup2(pipes[index][1], STDOUT_FILENO);
	return (0);
}

int	children(int **pipes, int *pids, t_list *commands)
{
	int	i;

	i = 0;
	while (commands)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (-1);
		if (pids[i] == 0)
		{
			char *temp[] = {"cat", "file1", NULL};
			io_redirection(commands, pipes, i);
			if (execve("/usr/bin/cat", temp, NULL) == -1)
				perror("execve");
		}
		commands = commands->next;
		i++;
	}
	return (0);
}

int	execute(t_list *commands)
{
	int	**pipes;
	int	*pids;
	int	i;
	int	cmd_count;
	
	i = 0;
	cmd_count = ft_lstsize(commands);
	pipes = ft_create_pipes(commands);
	pids = malloc(cmd_count * sizeof(int));
	if (!pipes)
		return (printf("Error creating pipes\n"), 1);
	children(pipes, pids, commands);
	while (i < cmd_count)
		waitpid(pids[i++], NULL, 0);
	return (0);
}
