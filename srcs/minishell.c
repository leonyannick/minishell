/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:47:38 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/28 11:00:58 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			continue ;
		add_history(line);
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
	rl_clear_history();
}
