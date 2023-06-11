/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:47:38 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/11 20:14:35 by aehrlich         ###   ########.fr       */
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
		execute(data.commands);
		ft_lstclear(&data.tokens, token_del);
		i++;
	}
	free(line);
}
	// int i = 11;
	
	// t_list *test = NULL;
	// t_list *node = ft_lstnew(&i);
	// ft_lstadd_back(&test, node);
	// ft_lstmap(test, print_token, free);