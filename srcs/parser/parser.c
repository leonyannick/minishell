/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:16:45 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/19 15:11:23 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser_utils.h"

/*
	checks the minishell BNF grammar:
	------------------------------------------------------
	pipeline		::=	cmd
					|	cmd PIPE pipline
				
	cmd				::=	{WORD} io_redirection WORD {WORD}
					|	WORD
					|	WORD {WORD}
				
	io_redirection	::=	I_RED | O_RED | O_RED | I_RED_HD
	------------------------------------------------------
	@argument - token:	token list to check
	@return:			true/flase
 */
static bool	ft_valid_grammar(t_list *token)
{
	t_token	*temp_token;
	t_list	*last;

	last = NULL;
	while (token)
	{
		temp_token = (t_token *)token->content;
		if (temp_token->type == PIPE)
		{
			if (!last || !token->next
				|| ((t_token *)last->content)->type == PIPE
				|| ((t_token *)token->next->content)->type == PIPE)
				return (printf("ushelless: syntax error near unexpected token '|'\n"), false);
		}
		else if (ft_is_redirection(temp_token->type))
		{
			if (!token->next)
				return (printf("ushelless: syntax error near unexpected token 'newline'\n"), false);
			if (((t_token *)token->next->content)->type != WORD)
				return (printf("ushelless: syntax error near unexpected token '%s'\n", ((t_token *)(token->next->content))->str), false);
		}
		last = token;
		token = token->next;
	}
	return (true);
}

/* 
	traverses the token linked list, splits at PIPES and populates the command,
	sets the pipes and the redirections depending on the token type.
	@argument - token_head: token list to traverse
	@argument - cmd:		pointer to cmd_head to update the head
 */
static void	ft_traverse_tokenlist(t_list *token_head, t_list **cmd_head)
{
	t_token		*temp_token;
	bool		is_first_word;
	int			cmd_idx;

	is_first_word = true;
	cmd_idx = 0;
	while (token_head)
	{
		temp_token = (t_token *)token_head->content;
		if (temp_token->type == PIPE)
		{
			ft_set_pipe(cmd_head, &is_first_word);
			cmd_idx++;
		}
		else if (temp_token->type == I_RED || temp_token->type == I_RED_HD)
			ft_set_input_redirection(&token_head, *cmd_head, cmd_idx);
		else if (temp_token->type == O_RED || temp_token->type == O_RED_APP)
			ft_set_output_redirection(&token_head, *cmd_head);
		else if (temp_token->type == WORD)
			ft_set_words(token_head, *cmd_head, &is_first_word);
		token_head = token_head->next;
	}
}

/* 
	parses the token linked list, extract piping and redircetion
	information, populating the command linked list.
	@argument - token_head:	head of token_linked list to parse
	@return:				linked list of simple commands
 */
t_list	*parse(t_list *token_head)
{
	t_list		*cmds;
	t_list		*cmd_head;

	if (!ft_valid_grammar(token_head) || !token_head)
		return (NULL);
	cmds = ft_create_cmd_list(token_head);
	if (!cmds)
		return (printf("Error creating cmd list\n"), NULL);
	cmd_head = cmds;
	ft_traverse_tokenlist(token_head, &cmds);
	return (cmd_head);
}
