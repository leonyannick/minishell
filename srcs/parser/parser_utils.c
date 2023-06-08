/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:31:46 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/08 13:19:13 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser_utils.h"

bool	ft_is_redirection(e_token_types type)
{
	return (type == I_RED || type == O_RED
		|| type == I_RED_HD || type == O_RED_APP);
}

void	ft_set_pipe(t_list **cmd_head, bool *is_first_word)
{
	t_command	*temp_cmd;

	temp_cmd = (t_command *)((*cmd_head)->content);
	temp_cmd->has_out_pipe = true;
	*cmd_head = (*cmd_head)->next;
	((t_command *)(*cmd_head)->content)->has_in_pipe = true;
	*is_first_word = true;
}

void	ft_set_input_redirection(t_list **token_head, t_list *cmd_head)
{
	t_command	*temp_cmd;
	t_token		*temp_token;

	temp_token = (t_token *)(*token_head)->content;
	temp_cmd = (t_command *)(cmd_head->content);
	temp_cmd->in_redir_type = temp_token->token_type;
	*token_head = (*token_head)->next;
	temp_token = (t_token *)(*token_head)->content;
	temp_cmd->input_redir_path = ft_strdup(temp_token->token_str);
}

void	ft_set_output_redirection(t_list **token_head, t_list *cmd_head)
{
	t_command	*temp_cmd;
	t_token		*temp_token;
	t_list		*temp_node;

	temp_token = (t_token *)(*token_head)->content;
	temp_cmd = (t_command *)(cmd_head->content);
	temp_cmd->out_redir_type = temp_token->token_type;
	*token_head = (*token_head)->next;
	temp_token = (t_token *)(*token_head)->content;
	temp_node = ft_lstnew((void *)temp_token->token_str);
	ft_lstadd_back(&(temp_cmd->output_redir_path), temp_node);
}

void	ft_set_words(t_list *token_head, t_list *cmd_head, bool *is_first_word)
{
	t_list		*temp_node;
	t_command	*temp_cmd;
	t_token		*temp_token;

	temp_cmd = (t_command *)(cmd_head->content);
	temp_token = (t_token *)token_head->content;
	if (*is_first_word)
		temp_cmd->type = ft_get_cmd_type(temp_token->token_str);
	*is_first_word = false;
	temp_node = ft_lstnew((void *)temp_token->token_str);
	ft_lstadd_back(&(temp_cmd->arguments), temp_node);
}
