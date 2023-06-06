/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:16:45 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/06 09:57:08 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/* t_arg_list	*arg_node_init(char *arg)
{
	t_arg_list *node;

	node = malloc(sizeof(t_arg_list));
	node->arg = malloc(ft_strlen(arg) + 1);
	ft_strlcpy(node->arg, arg, ft_strlen(arg) + 1);
	node->next = NULL;
	return (node);
}

t_token	*token_init(char *str, e_tokentype type)
{
	t_token *token = malloc(sizeof(t_token));
	token->str = malloc(sizeof(ft_strlen(str) + 1));
	ft_strlcpy(token->str, str, ft_strlen(str) + 1);
	token->type = type;
	token->next = NULL;
	return (token);
}

t_command *cmd_init(t_token **token_list)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->arguments = NULL;
	cmd->input_redir_path = NULL;
	cmd->output_redir_path = NULL;
	cmd->in_redir_type = none;
	cmd->out_redir_type = none;
	
	if ((*token_list)->type == _pipe)
	{
		cmd->in_redir_type = _pipe;
		(*token_list) = (*token_list)->next;
	}
	while ((*token_list) != NULL && (*token_list)->type != _pipe)
	{
		if ((*token_list)->type == builtin_cmd)
		{
			cmd->cmd_name = malloc(ft_strlen((*token_list)->str) + 1);
			ft_strlcpy(cmd->cmd_name, (*token_list)->str, ft_strlen((*token_list)->str) + 1);
			cmd->type = builtin_cmd;
		}
		else if ((*token_list)->type == path_cmd)
		{
			cmd->cmd_name = malloc(ft_strlen((*token_list)->str) + 1);
			ft_strlcpy(cmd->cmd_name, (*token_list)->str, ft_strlen((*token_list)->str) + 1);
			cmd->type = path_cmd;
		}
		else if ((*token_list)->type == argument)
		{
			if (cmd->arguments == NULL)
				cmd->arguments = arg_node_init((*token_list)->str);
			else
				arg_list_add_back(&(cmd->arguments), arg_node_init((*token_list)->str));
		}
		else if ((*token_list)->type == redir_in)
		{
			cmd->in_redir_type = redir_in;
			(*token_list) = (*token_list)->next;
			cmd->input_redir_path = malloc(ft_strlen((*token_list)->str) + 1);
			ft_strlcpy(cmd->input_redir_path, (*token_list)->str, ft_strlen((*token_list)->str) + 1);
		}
		else if ((*token_list)->type == redir_in_heredoc)
			cmd->in_redir_type = redir_in_heredoc;
		else if ((*token_list)->type == redir_out)
		{
			cmd->out_redir_type = redir_out;
			(*token_list) = (*token_list)->next;
			cmd->output_redir_path = malloc(ft_strlen((*token_list)->str) + 1);
			ft_strlcpy(cmd->output_redir_path, (*token_list)->str, ft_strlen((*token_list)->str) + 1);
		}
		else if ((*token_list)->type == redir_out_append)
		{
			cmd->out_redir_type = redir_out_append;
			(*token_list) = (*token_list)->next;
			cmd->output_redir_path = malloc(ft_strlen((*token_list)->str) + 1);
			ft_strlcpy(cmd->output_redir_path, (*token_list)->str, ft_strlen((*token_list)->str) + 1);
		}
		(*token_list) = (*token_list)->next;
		if ((*token_list) && (*token_list)->type == _pipe)
			cmd->out_redir_type = _pipe;
	}
	return (cmd);
}

void	print_cmd_list(t_command *head)
{
	int count = 1;
	
	while (head)
	{
		printf("\nCOMMAND %d:\n\n", count++);
		printf("name:\t\t%s\n", (head)->cmd_name);
		printf("args:\t\t");
		if (head->arguments == NULL)
			printf("NULL");
		while (head->arguments)
		{
			printf("%s; ", head->arguments->arg);
			head->arguments = head->arguments->next;
		}
		printf("\n");
		if (head->type == builtin_cmd)
			printf("type:\t\tbuiltin_command\n");
		if (head->type == path_cmd)
			printf("type:\t\tpath_command\n");
		if (head->in_redir_type == redir_in)
			printf("in_redir_type:\t<\n");
		else if (head->in_redir_type == redir_in_heredoc)
			printf("in_redir_type:\t<<\n");
		else if (head->in_redir_type == _pipe)
			printf("in_redir_type:\tPIPE\n");
		else
			printf("in_redir_type:\tno input redirection\n");
		if (head->out_redir_type == redir_out)
			printf("out_redir_type:\t>\n");
		else if (head->out_redir_type == redir_out_append)
			printf("out_redir_type:\t>>\n");
		else if (head->out_redir_type == _pipe)
			printf("out_redir_type:\tPIPE\n");
		else
			printf("out_redir_type:\tno output redirection\n");
		if (head->input_redir_path == NULL)
			printf("in_redir_path:\tNULL\n");
		else
			printf("in_redir_path:\t%s\n", head->input_redir_path);
		if (head->output_redir_path == NULL)
			printf("out_redir_path:\tNULL\n");
		else
			printf("out_redir_path:\t%s\n", head->output_redir_path);
		printf("\n");
		head = (head)->next;
	}
} */
#include "../includes/minishell.h"

e_word_type	get_word_type(t_list *token)
{
	t_token *casted = (t_token *)token;
	
	if (casted->token_type)
}

bool	ft_is_redirection(t_token *token)
{
	if (token->token_type == I_RED)
		return (true);
	if (token->token_type == I_RED_HD)
		return (true);
	if (token->token_type == O_RED)
		return (true);
	if (token->token_type == O_RED_APP)
		return (true);
	return (false);
}

void	ft_set_redirection(t_list **token_head, t_command **cmd)
{
	//set redirection and increse token to get the path, what happens if no path is givengit 
}

void	ft_set_word(t_list **token, t_command **cmd)
{
	
}

t_command	*create_command(t_list **token_head)
{
	t_command	*cmd;
	t_token		*tmp_token;
	
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	if (((t_token *)(*token_head))->token_type == PIPE)
	{
		cmd->in_redir_type = PIPE;
		cmd->input_redir_path = NULL;
		(*token_head) = (*token_head)->next;
	}
	while (*token_head)
	{
		tmp_token = (t_token *)(*token_head)->content;
		if (ft_is_redirection(*token_head))
			ft_set_redirection(token_head, &cmd);
		if (tmp_token->token_type == WORD)
			ft_set_word(token_head, &cmd);
		if 
		
			
	}
	
}

t_list	**parse(t_list **token_head)
{
	t_list		**cmd_head;
	t_command	*temp_cmd;
	t_list		*temp_node;

	cmd_head = NULL;
	if (!token_head || !(*token_head))
		return (NULL);
	while (*token_head)
	{
		temp_cmd = create_command(token_head);
		if (!temp_cmd)
			return (NULL);
		temp_node = ft_lstnew((void *)temp_cmd);
		if (!cmd_head)
			cmd_head = &temp_node;
		else
			ft_lstadd_back(cmd_head, temp_node);
		
	}
	return (cmd_head);
}
