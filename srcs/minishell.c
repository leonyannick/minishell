/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:03:36 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/07 16:05:30 by aehrlich         ###   ########.fr       */
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

void	print_string_list(t_list *head)
{
	while (head)
	{
		printf("%s -> ", (char *)head->content);
		head = head->next;
	}
	printf("NULL\n");
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

	t_list	*token_head;
	t_list	*cmd_head;

	//echo Hello "$name" | grep Hello | > ./outfile cat
	t_list *t1 = ft_lstnew((void *)assign_token_attr("\"echo\"", WORD));
	token_head = t1;
	t_list *t2 = ft_lstnew((void *)assign_token_attr("\"Hello\"", WORD));
	t1->next = t2;
	t_list *t3 = ft_lstnew((void *)assign_token_attr("\"$name\"", WORD));
	t2->next = t3;
	t_list *t4 = ft_lstnew((void *)assign_token_attr("\"|\"", PIPE));
	t3->next = t4;
	t_list *t5 = ft_lstnew((void *)assign_token_attr("\"grep\"", WORD));
	t4->next = t5;
	t_list *t6 = ft_lstnew((void *)assign_token_attr("\"Hello\"", WORD));
	t5->next = t6;
	t_list *t7 = ft_lstnew((void *)assign_token_attr("\"|\"", PIPE));
	t6->next = t7;
	t_list *t8 = ft_lstnew((void *)assign_token_attr("\">\"", O_RED));
	t7->next = t8;
	t_list *t9 = ft_lstnew((void *)assign_token_attr("\"./out1\"", WORD));
	t8->next = t9;
	t_list *t10 = ft_lstnew((void *)assign_token_attr("\">>\"", O_RED_APP));
	t9->next = t10;
	t_list *t11 = ft_lstnew((void *)assign_token_attr("\"./out2\"", WORD));
	t10->next = t11;
	t_list *t12 = ft_lstnew((void *)assign_token_attr("\"cat\"", WORD));
	t11->next = t12;

	printf("TOKEN LINKED LIST:\n");
	t_list *temp = token_head;
	t_token *temp_token;
	
	while (temp)
	{
		temp_token = (t_token *)temp->content;
		printf("%s -> ", temp_token->token_str);
		temp = temp->next;
	}
	printf("NULL\n-----------------------------------\n");
	cmd_head = parse(token_head);
	t_command *temp_cmd;
	
	while (cmd_head)
	{
		temp_cmd = (t_command *)cmd_head->content;
		printf("COMMAND %s:\n\n", (char *)temp_cmd->arguments->content);
		printf("arg list:\t");
		print_string_list(temp_cmd->arguments);
		printf("cmd type:\t");
		if (temp_cmd->type == BUILTIN)
			printf("BUILTIN\n");
		else
			printf("PATH\n");
		printf("in pipe:\t");
		if (temp_cmd->has_in_pipe)
			printf("TRUE\n");
		else
			printf("FALSE\n");
		printf("out pipe:\t");
		if (temp_cmd->has_out_pipe)
			printf("TRUE\n");
		else
			printf("FALSE\n");
		printf("in redir:\t");
		if (temp_cmd->in_redir_type == NONE)
			printf("NONE\n");
		else if (temp_cmd->in_redir_type == I_RED)
			printf("I_RED (<)\n");
		else if (temp_cmd->in_redir_type == I_RED_HD)
			printf("I_RED_HD (<<)\n");
		printf("out redir:\t");
		if (temp_cmd->out_redir_type == NONE)
			printf("NONE\n");
		else if (temp_cmd->out_redir_type == O_RED)
			printf("O_RED (>)\n");
		else if (temp_cmd->out_redir_type == O_RED_APP)
			printf("O_RED_APP (>>)\n");
		printf("in redir path:\t");
		printf("%s\n", temp_cmd->input_redir_path);
		printf("out redir path:\t");
		print_string_list(temp_cmd->output_redir_path);
		printf("------------------------------------\n");
		cmd_head = cmd_head->next;
	}
	
	return (0);
}
