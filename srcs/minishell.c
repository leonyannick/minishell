/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:03:36 by lbaumann          #+#    #+#             */
/*   Updated: 2023/05/31 13:04:30 by lbaumann         ###   ########.fr       */
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

void	*print_token(void *arg)
{
	printf("[%s]\t", ((t_token *)arg)->token_str);
	print_enum(((t_token *)arg)->token_type);
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	t_list	*tokens;

	memset(&data, 0, sizeof(t_data));
	init_data(&data, envp);
	printf("%s\n", data.envp[0]);
	
	while(1)
	{
		line = readline("ushelless:> ");
		if (!line)
			continue ;
		tokens = scan_tokens(line);
		// printList(tokens);
		ft_lstmap(tokens, print_token, free);
	}
}
