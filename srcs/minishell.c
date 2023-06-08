/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:03:36 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/08 12:14:54 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "./parser/parser_utils.h" //for printing, delete later

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
	{void	print_token_list(t_list *token)
		line = readline("ushelless:>");
		if (!line)
			continue ;
	} */

	t_list	*token_head;
	t_list	*cmd_head;

	//echo Hello "$name" | grep Hello | > ./outfile cat
	t_list *t1 = ft_lstnew((void *)assign_token_attr("echo", WORD));
	token_head = t1;
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
	t_list *t9 = ft_lstnew((void *)assign_token_attr("./out1", WORD));
	t8->next = t9;
	t_list *t10 = ft_lstnew((void *)assign_token_attr(">>", O_RED_APP));
	t9->next = t10;
	t_list *t11 = ft_lstnew((void *)assign_token_attr("./out2", WORD));
	t10->next = t11;
	t_list *t12 = ft_lstnew((void *)assign_token_attr("cat", WORD));
	t11->next = t12;

	print_token_list(token_head);
	cmd_head = parse(token_head);
	print_cmd_list(cmd_head);
	
	return (0);
}
