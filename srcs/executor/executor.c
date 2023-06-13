/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:58:03 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/13 12:32:39 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

static int	**ft_create_pipes(t_list *commands)
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

int	children(int **pipes, int *pids, t_data *data)
{
	int			i;
	t_list		*cmd_head;
	t_command	*command;
	
	i = 0;
	cmd_head = data->commands;
	while (cmd_head)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (-1);
		if (pids[i] == 0)
		{
			command = (t_command *)cmd_head->content;
			//char *temp[] = {"cat", "file1", NULL};
			io_redirection(cmd_head, pipes, i);
			execute_path_cmd(data, command);
			/* if (execve("/usr/bin/cat", temp, NULL) == -1)
				perror("execve"); */
		}
		cmd_head = cmd_head->next;
		i++;
	}
	return (0);
}

int	execute(t_data *data)
{
	int	**pipes;
	int	*pids;
	int	i;
	int	cmd_count;
	
	i = 0;
	if (!data->commands)
		return (1);
	cmd_count = ft_lstsize(data->commands);
	pipes = ft_create_pipes(data->commands);
	pids = malloc(cmd_count * sizeof(int));
	if (!pipes)
		return (printf("Error creating pipes\n"), 1);
	children(pipes, pids, data);
	while (i < cmd_count)
		waitpid(pids[i++], NULL, 0);
	return (0);
}
