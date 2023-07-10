/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:47:38 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/10 15:16:56 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

static void	main_loop(char *line, t_data *data)
{
	while(1)
	{
		line = readline("ushelless:> ");
		if (!line)
			exit_gracefully(data);
		else if (*line == '\0')
			continue ;
		add_history(line);
		data->tokens = scan_tokens(line, data);
		data->commands = parse(data->tokens);
		if (data->commands)
			g_exit_code = execute(data);
		ft_lstclear(&data->tokens, token_del);
		ft_lstclear(&data->commands, command_del);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	
	if (argc > 1)
		return (0);
	line = NULL;
	argv = NULL;
	init_data(&data, envp);
	main_loop(line, &data);
}
