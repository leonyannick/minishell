/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:31:46 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/19 15:13:50 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser_utils.h"

/* 
	returns boolean when passedtype is a redircetion
 */
bool	ft_is_redirection(e_token_types type)
{
	return (type == I_RED || type == O_RED
		|| type == I_RED_HD || type == O_RED_APP);
}

/* 
	If a token is of type PIPE the current command is set to have
	an outpipe. Going to the next command and sets this to have an inpipe.
	@argument - cmd_head: pointer to head of commandlist, to update head
	@argument - is_first_word: after a pipe the next word should be 
	interpreted as first
								word to determine if the word should be a command name
	@return						none
 */
void	ft_set_pipe(t_list **cmd_head, bool *is_first_word)
{
	t_command	*temp_cmd;

	temp_cmd = (t_command *)((*cmd_head)->content);
	temp_cmd->has_out_pipe = true;
	*cmd_head = (*cmd_head)->next;
	((t_command *)(*cmd_head)->content)->has_in_pipe = true;
	*is_first_word = true;
}

char	*creat_unique_hd_filename(int cmd_idx)
{
	static int	hd_idx = 0;
	char		*filename;

	filename = ft_strdup(".heredoc_");
	filename = ft_strjoin_free(filename, ft_itoa(cmd_idx));
	filename = ft_strjoin_free(filename, "_");
	filename = ft_strjoin_free(filename, ft_itoa(hd_idx++));
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
void	ft_set_input_redirection(t_list **token_head, t_list *cmd_head, int cmd_idx)
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
		new_file->path = creat_unique_hd_filename(cmd_idx);
		new_file->herdoc_lim = ft_strdup(temp_token->str);
	}
	temp_node = ft_lstnew((void *)new_file);
	ft_lstadd_back(&(temp_cmd->inred_file), temp_node);
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
	temp_node = ft_lstnew((void *)new_file);
	ft_lstadd_back(&(temp_cmd->outred_file), temp_node);
}

/* 
	creates a node for every WORD. The node is added to the end of the argument
	linked list. The first WORD is used to determine the command type.
	is_first_word is then set to false. Is set to true after the next
	PIPE when we facing a new command.
	@argument - token_head: tokenhead
	@argument - cmd_head:	current cmd to be set
	@return:				none
 */
void	ft_set_words(t_list *token_head, t_list *cmd_head, bool *is_first_word)
{
	t_list		*temp_node;
	t_command	*temp_cmd;
	t_token		*temp_token;

	temp_cmd = (t_command *)(cmd_head->content);
	temp_token = (t_token *)token_head->content;
	if (*is_first_word)
		temp_cmd->type = ft_get_cmd_type(temp_token->str);
	*is_first_word = false;
	temp_node = ft_lstnew((void *)ft_strdup(temp_token->str));
	ft_lstadd_back(&(temp_cmd->arguments), temp_node);
}
