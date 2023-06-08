/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:16:45 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/08 12:23:16 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser_utils.h"

bool	ft_valid_grammar(t_list *token)
{
	t_token	*temp_token;
	t_list	*last;

	last = NULL;
	while (token)
	{
		temp_token = (t_token *)token->content;
		if (temp_token->token_type == PIPE)
		{
			if (!last || !token->next
				|| ((t_token *)last->content)->token_type == PIPE
				|| ((t_token *)token->next->content)->token_type == PIPE)
				return (printf("parse error near |\n"), false);
		}
		else if (temp_token->token_type <= 3)
		{
			if (!token->next
				||((t_token *)token->next->content)->token_type != WORD)
				return (printf("parse error near redirection\n"), false);
		}
		last = token;
		token = token->next;
	}
	return (true);
}

t_list	*parse(t_list *token_head)
{
	t_list		*cmds;
	t_list		*cmd_head;
	t_token		*temp_token;
	t_command	*temp_cmd;
	t_list		*temp_node;
	bool		is_first_word;

	if (!ft_valid_grammar(token_head))
		return (NULL);
	cmds = ft_create_cmd_list(token_head);
	is_first_word = true;
	if (!cmds)
		return (printf("Error creating cmd list\n"), NULL);
	cmd_head = cmds;
	while (token_head)
	{
		temp_token = (t_token *)token_head->content;
		temp_cmd = (t_command *)(cmds->content);
		if (temp_token->token_type == PIPE)
		{
			temp_cmd->has_out_pipe = true;
			cmds = cmds->next;
			((t_command *)cmds->content)->has_in_pipe = true;
			is_first_word = true;
		}
		else if (temp_token->token_type == I_RED || temp_token->token_type == I_RED_HD)
		{
			temp_cmd->in_redir_type = temp_token->token_type;
			token_head = token_head->next;
			temp_token = (t_token *)token_head->content;
			temp_cmd->input_redir_path = ft_strdup(temp_token->token_str);
		}
		else if (temp_token->token_type == O_RED || temp_token->token_type == O_RED_APP)
		{
			temp_cmd->out_redir_type = temp_token->token_type;
			token_head = token_head->next;
			temp_token = (t_token *)token_head->content;
			temp_node = ft_lstnew((void *)temp_token->token_str);
			ft_lstadd_back(&(temp_cmd->output_redir_path), temp_node);
		}
		else if (temp_token->token_type == WORD)
		{
			if (is_first_word)
				temp_cmd->type = ft_get_cmd_type(temp_token->token_str);
			is_first_word = false;
			temp_node = ft_lstnew((void *)temp_token->token_str);
			ft_lstadd_back(&(temp_cmd->arguments), temp_node);
		}
		token_head = token_head->next;
	}
	return (cmd_head);
}
