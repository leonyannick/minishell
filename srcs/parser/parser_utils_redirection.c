/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:17:09 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/27 10:34:22 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

static char	*creat_unique_hd_filename(void)
{
	static int	hd_idx = 0;
	char		*filename;
	char		*idx_string;

	idx_string = ft_itoa(hd_idx++);
	filename = ft_strjoin("/tmp/.heredoc_", idx_string);
	idx_string = ft_free_set_null(idx_string);
	return (filename);
}

/* 
	overides the input_red (if more input_redir appear in tokenstream) and
	goes to next token to set the following WORD as the path. 
	If there was alredy one, free the old one.
	@argument - token_head:	Pointer to tokenhead, to be able to update the head
	@argument - cmd_head:	Pointer to current cmd to be set
	@return:				none
 */
void	ft_set_input_redirection(t_list **token_head, t_list *cmd_head)
{
	t_command	*temp_cmd;
	t_token		*temp_token;
	t_file		*new_file;

	new_file = malloc(sizeof(t_file));
	if (!new_file)
		return ;
	temp_token = (t_token *)(*token_head)->content;
	temp_cmd = (t_command *)(cmd_head->content);
	temp_cmd->in_redir_type = temp_token->type;
	new_file->open_mode = temp_token->type;
	*token_head = (*token_head)->next;
	temp_token = (t_token *)(*token_head)->content;
	new_file->fd = -1;
	if (temp_cmd->in_redir_type == I_RED)
	{
		new_file->path = ft_strdup(temp_token->str);
		new_file->herdoc_lim = NULL;
	}
	else if (temp_cmd->in_redir_type == I_RED_HD)
	{
		new_file->path = creat_unique_hd_filename();
		new_file->herdoc_lim = ft_strdup(temp_token->str);
	}
	ft_lstadd_back(&(temp_cmd->inred_file), ft_lstnew((void *)new_file));
}

/* 
	creates a node for every out_redirection because it get
	not overwritten like in input. for every out_redir a file 
	has to be created. The node is added to the end of the out_red
	linked list. The file descriptor gets set in executor module.
	@argument - token_head:	Pointer to tokenhead, to be able to update the head
	@argument - cmd_head:	Pointer to current cmd to be set
	@return:				none
 */
void	ft_set_output_redirection(t_list **token_head, t_list *cmd_head)
{
	t_command	*temp_cmd;
	t_token		*temp_token;
	t_list		*temp_node;
	t_file		*new_file;

	new_file = malloc(sizeof(t_file));
	if (!new_file)
		return ;
	temp_token = (t_token *)(*token_head)->content;
	temp_cmd = (t_command *)(cmd_head->content);
	temp_cmd->out_redir_type = temp_token->type;
	new_file->open_mode = temp_token->type;
	*token_head = (*token_head)->next;
	temp_token = (t_token *)(*token_head)->content;
	new_file->fd = -1;
	new_file->path = ft_strdup(temp_token->str);
	new_file->herdoc_lim = NULL;
	temp_node = ft_lstnew((void *)new_file);
	ft_lstadd_back(&(temp_cmd->outred_file), temp_node);
}
