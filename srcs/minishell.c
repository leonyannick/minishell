/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:47:38 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/13 17:06:05 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	argc = 0;
	argv = NULL;
	init_data(&data, envp);
	
	int i = 0;
	while(1)
	{
		line = readline("ushelless:> ");
		if (!line)
			continue ;
		data.tokens = scan_tokens(line, &data);
		//ft_lstiter(data.tokens, print_token);
		data.commands = parse(data.tokens);
		//print_cmd_list(data.commands);
		execute(&data);
		ft_lstclear(&data.tokens, token_del);
		i++;
	}
	free(line);
}
