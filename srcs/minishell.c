/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:03:36 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/01 12:44:30 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_enum(e_token_types type)
{
	if (type == O_RED)
		printf("O_RED\n");
	else if (type == I_RED)
		printf("I_RED\n");
	else if (type == I_RED)
		printf("I_RED\n");
	else if (type == I_RED_HD)
		printf("I_RED_HD\n");
	else if (type == O_RED_APP)
		printf("O_RED_APP\n");
	else if (type == EQUALS)
		printf("EQUALS\n");
	else if (type == PIPE)
		printf("PIPE\n");
	else if (type == WORD)
		printf("WORD\n");
	else if (type == DQUOTES)
		printf("DQUOTES\n");
	else if (type == SQUOTES)
		printf("SQUOTES\n");
	else if (type == PARAMETER)
		printf("PARAMETER\n");
	else if (type == WHITESPACE)
		printf("WHITESPACE\n");
}

void	print_token(void *arg)
{
	printf("[%s]\t", ((t_token *)arg)->token_str);
	print_enum(((t_token *)arg)->token_type);
	// return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	argc = 0;
	argv = NULL;
	ft_memset(&data, 0, sizeof(t_data));
	init_data(&data, envp);
	
	while(1)
	{
		line = readline("ushelless:> ");
		if (!line)
			continue ;
		char **split_arr = ft_split(line, ' ');
		
		data.tokens = scan_tokens(line, &data);
		// // printList(tokens);
		ft_lstiter(data.tokens, print_token);
		// ft_lstmap(data.tokens, print_token, free);
	}
}
	// int i = 11;
	
	// t_list *test = NULL;
	// t_list *node = ft_lstnew(&i);
	// ft_lstadd_back(&test, node);
	// ft_lstmap(test, print_token, free);
