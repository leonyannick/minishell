/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:03:36 by lbaumann          #+#    #+#             */
/*   Updated: 2023/05/25 10:55:21 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*assign_token_attr(char *token_str, e_token_types type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->token_str = token_str;
	token->token_type = type;
	return (token);
}

int	main(void)
{
	/* char	*line;

	while(1)
	{
		line = readline("ushelless:>");
		if (!line)
			continue ;
	} */

	t_list **token_head;

	//echo Hello "$name" | grep Hello | > ./outfile cat
	t_list *t1 = ft_lstnew((void *)assign_token_attr("echo", WORD));
	token_head = &t1;
	t_list *t2 = ft_lstnew((void *)assign_token_attr("Hello", WORD));
	t1->next = t2;
	t_list *t3 = ft_lstnew((void *)assign_token_attr("\"$name\"", WORD));
	t2->next = t3;
	t_list *t4 = ft_lstnew((void *)assign_token_attr("|", PIPE));
	t3->next = t4;
	t_list *t5 = ft_lstnew((void *)assign_token_attr("grep", WORD));
	t4->next = t5;
	t_list *t6 = ft_lstnew((void *)assign_token_attr("Hello", WORD));
	t5->next = t6;
	t_list *t7 = ft_lstnew((void *)assign_token_attr("|", PIPE));
	t6->next = t7;
	t_list *t8 = ft_lstnew((void *)assign_token_attr(">", O_RED));
	t7->next = t8;
	t_list *t9 = ft_lstnew((void *)assign_token_attr("./outfile", WORD));
	t8->next = t9;
	t_list *t10 = ft_lstnew((void *)assign_token_attr("cat", WORD));
	t9->next = t10;

	printf("TOKEN LINKED LIST:\n");
	t_list *temp = *token_head;
	t_token *temp_token;
	
	while (temp)
	{
		temp_token = (t_token *)temp->content;
		printf("%s -> ", temp_token->token_str);
		temp = temp->next;
	}
	printf("NULL\n-----------------------------------\n");
	
	/* while (*token_head)
	{
		if (cmd_head == NULL)
		{
			cmd = cmd_init(token_head);
			cmd_head = &cmd;
		}
		else
			cmd_list_add_back(cmd_head, cmd_init(token_head));
	}
	print_cmd_list(*cmd_head); */
	return (0);
}
