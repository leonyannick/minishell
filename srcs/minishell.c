/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:47:38 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/20 09:24:59 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	int		exec_return;

	argc = 0;
	argv = NULL;
	init_data(&data, envp);
	
	while(1)
	{
		line = readline("ushelless:> ");
		if (!line)
			continue ;
		if (ft_strcmp(line, "exit") == 0) //free stuff
			exit(0);
		data.tokens = scan_tokens(line, &data);
		data.commands = parse(data.tokens);
		exec_return = execute(&data);
		ft_lstclear(&data.tokens, token_del);
		delete_heredocs(&data);
		ft_lstclear(&data.commands, command_del);
		if (exec_return == -1)
			break ;
	}
	free(line);
}
