/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:58:03 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/11 20:30:54 by aehrlich         ###   ########.fr       */
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

int	execute(t_list *commands)
{
	int	**pipes;
	int	*pids;
	int	i;
	
	i = 0;
	pipes = ft_create_pipes(commands);
	if (!pipes)
		return (printf("Error creating pipes\n"), 1);
	return (0);
}
