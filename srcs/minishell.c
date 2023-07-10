/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:47:38 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/07 16:59:02 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

void	exit_gracefully(t_data *data)
{
	printf("exit\n");
	if (data->line)
		data->line = ft_free_set_null(data->line);
	if (data->env_dict)
		ft_lstclear(&data->env_dict, ft_dict_node_del);
	if (data->tokens)
		ft_lstclear(&data->tokens, token_del);
	if (data->commands)
		ft_lstclear(&data->commands, command_del);
	rl_clear_history();
	exit(g_exit_code);
}

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
		g_exit_code = execute(data);
		ft_lstclear(&data->tokens, token_del);
		delete_heredocs(data);
		ft_lstclear(&data->commands, command_del);
		if (g_exit_code == EXIT_BREAK)
			break ;
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
	exit_gracefully(&data);
}
