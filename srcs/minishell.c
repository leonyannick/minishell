/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:47:38 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/07 10:54:17 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	int		exec_return;
	
	if (argc > 1)
		return (0);
	argv = NULL;
	init_data(&data, envp);
	while(1)
	{
		line = readline("ushelless:> ");
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		else if (*line == '\0')
			continue ;
		add_history(line);
		data.tokens = scan_tokens(line, &data);
		data.commands = parse(data.tokens);
		exec_return = execute(&data);
		ft_lstclear(&data.tokens, token_del);
		delete_heredocs(&data);
		ft_lstclear(&data.commands, command_del);
		if (exec_return == EXIT_BREAK)
			break ;
	}
	free(line);
	rl_clear_history();
}
