/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:03:36 by lbaumann          #+#    #+#             */
/*   Updated: 2023/05/23 20:36:55 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*printToken(void *arg)
{
	printf("%s\n", ((t_token *)arg)->tokenStr);
	return (NULL);
}

void printList(t_list *node)
{
	while (node != NULL)
	{
		printf(" %s ", ((t_token *)node->content)->tokenStr);
		node = node->next;
	}
}

int	main(void)
{
	char	*line;
	t_list	*tokens;

	while(1)
	{
		line = readline("ushelless:>");
		if (!line)
			continue ;
		tokens = getTokens(line);
		// printList(tokens);
		ft_lstmap(tokens, printToken, free);
	}
}
