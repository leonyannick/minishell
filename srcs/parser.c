/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:16:45 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/07 16:03:04 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

unsigned int	ft_cmd_count(t_list *token)
{
	unsigned int count;

	count = 0;
	while (token)
	{
		if (((t_token *)token->content)->token_type == PIPE)
			count++;
	token = token->next;
	}
	return (count + 1);
}

t_command	*ft_create_cmd(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->arguments = NULL;
	cmd->type = PATH;
	cmd->has_in_pipe = false;
	cmd->has_out_pipe = false;
	cmd->in_redir_type = NONE;
	cmd->out_redir_type = NONE;
	cmd->input_redir_path = NULL;
	cmd->output_redir_path = NULL;
	return (cmd);
}

t_list		*ft_create_cmd_list(t_list *token_head)
{
	int			i;
	t_command	*temp_cmd;
	t_list		*temp_node;
	t_list		*cmd_list;

	cmd_list = NULL;
	if (!token_head)
		return (printf("Tokenhead NULL\n"), NULL);
	i = ft_cmd_count(token_head);
	while (i--)
	{
		temp_cmd = ft_create_cmd();
		if (!temp_cmd)
			return (NULL); //TODO: Free list
		temp_node = ft_lstnew((void *)temp_cmd);
		if (!temp_node)
			return (NULL); //TODO: Free list
		ft_lstadd_back(&cmd_list, temp_node);
	}
	return (cmd_list);
}

e_cmd_type ft_get_cmd_type(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"))
	{
		return (BUILTIN);
	}
	return (PATH);
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
		return (printf("Error creating cmd list\n"), NULL); //TODO
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
			{
				temp_cmd->type = ft_get_cmd_type(temp_token->token_str);
				is_first_word = false;
			}
			temp_node = ft_lstnew((void *)temp_token->token_str);
			ft_lstadd_back(&(temp_cmd->arguments), temp_node);
		}
		token_head = token_head->next;
	}
	return (cmd_head);
}
