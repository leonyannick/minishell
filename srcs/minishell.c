/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:47:38 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/21 13:41:04 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*rl_gets(char *line_read)
{
	line_read = ft_free_set_null(line_read);
	line_read = readline("ushelless:> ");

	if (line_read && *line_read)
		add_history(line_read);

	return (line_read);
}

void	rl_cleanup(char *line_read)
{
	line_read = ft_free_set_null(line_read);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	static char	*line_read;

	argc = 0;
	argv = NULL;
	init_data(&data, envp);
	
	int i = 0;
	while(1)
	{
		line_read = rl_gets(line_read);
		if (!line_read)
			continue ;
		printf("%s\n", line_read);
		
	}
	rl_cleanup(line_read);
}
	// int i = 11;
	
	// t_list *test = NULL;
	// t_list *node = ft_lstnew(&i);
	// ft_lstadd_back(&test, node);
	// ft_lstmap(test, print_token, free);