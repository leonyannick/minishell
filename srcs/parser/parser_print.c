/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:23:40 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/08 15:38:02 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser_utils.h"

void	print_cmd_list(t_list *cmd_head)
{
	t_command *temp_cmd;
	
	while (cmd_head)
	{
		temp_cmd = (t_command *)cmd_head->content;
		if (temp_cmd->arguments)
			printf("COMMAND: %s:\n\n", (char *)temp_cmd->arguments->content);
		else 
			printf("COMMAND: no command\n\n");
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

void	print_token_list(t_list *token)
{
	printf("TOKEN LINKED LIST:\n");
	t_token *temp_token;
	
	while (token)
	{
		temp_token = (t_token *)token->content;
		printf("%s -> ", temp_token->token_str);
		token = token->next;
	}
	printf("NULL\n-----------------------------------\n");
}