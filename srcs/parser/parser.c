/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:16:45 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/08 13:21:57 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser_utils.h"

static bool	ft_valid_grammar(t_list *token)
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
		else if (ft_is_redirection(temp_token->token_type))
		{
			if (!token->next
				|| ((t_token *)token->next->content)->token_type != WORD)
				return (printf("parse error near redirection\n"), false);
		}
		last = token;
		token = token->next;
	}
	return (true);
}

static void	ft_traverse_tokenlist(t_list *token_head, t_list **cmd_head)
{
	t_token		*temp_token;
	bool		is_first_word;

	is_first_word = true;
	while (token_head)
	{
		temp_token = (t_token *)token_head->content;
		if (temp_token->token_type == PIPE)
			ft_set_pipe(cmd_head, &is_first_word);
		else if (temp_token->token_type == I_RED || temp_token->token_type == I_RED_HD)
			ft_set_input_redirection(&token_head, *cmd_head);
		else if (temp_token->token_type == O_RED || temp_token->token_type == O_RED_APP)
			ft_set_output_redirection(&token_head, *cmd_head);
		else if (temp_token->token_type == WORD)
			ft_set_words(token_head, *cmd_head, &is_first_word);
		token_head = token_head->next;
	}
}

t_list	*parse(t_list *token_head)
{
	t_list		*cmds;
	t_list		*cmd_head;

	if (!ft_valid_grammar(token_head))
		return (NULL);
	cmds = ft_create_cmd_list(token_head);
	if (!cmds)
		return (printf("Error creating cmd list\n"), NULL);
	cmd_head = cmds;
	ft_traverse_tokenlist(token_head, &cmds);
	return (cmd_head);
}
