/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:03:36 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/06 11:04:31 by lbaumann         ###   ########.fr       */
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
	while(i < 1)
	{
		line = readline("ushelless:> ");
		if (!line)
			continue ;
		
		data.tokens = scan_tokens(line, &data);
		ft_lstiter(data.tokens, print_token);
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
