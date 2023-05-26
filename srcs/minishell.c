/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:03:36 by lbaumann          #+#    #+#             */
/*   Updated: 2023/05/26 12:12:50 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	memset(&data, 0, sizeof(t_data));
	init_data(&data, envp);
	printf("%s\n", data.envp[0]);
	
	while(1)
	{
		line = readline("ushelless:>");
		if (!line)
			continue ;
	}
}
