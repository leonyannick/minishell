/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_postprocess.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:10:21 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/17 09:50:55 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

/**
 * called from main lexer function (scan_tokens)
 * goes through the token list and applies some post-procesing before
 * handing it off to the parser
*/
t_list	*tokens_postprocess(t_list *tokens)
{
	tokens = modify_list(&tokens, word_splitting);
	tokens = modify_list(&tokens, merge_words);
	tokens = modify_list(&tokens, remove_whitespace);
	return (tokens);
}

/**
 * iterate the lexer linked list and apply function f to each node
*/
t_list	*modify_list(t_list **lst, t_list *(*f)(t_list **lst, t_list *node))
{
	t_list	*node;
	t_list	*next;

	node = *lst;
	while (node)
	{
		next = node->next;
		*lst = (*f)(lst, node);
		node = next;
	}
	return (*lst);
}

/**
 * parameters that are expanded outside double quotes are split using
 * whitespace as the delimiter into single tokens
*/
t_list	*word_splitting(t_list **tokens, t_list *node)
{
	char			*token_str;
	t_list			*token_after_exp;
	t_token_types	type;
	size_t			i;

	if (((t_token *)node->content)->type == PARAMETER)
	{
		token_str = ((t_token *)node->content)->str;
		i = 0;
		token_after_exp = node->next;
		while (token_str[i])
		{
			if (is_whitespace(token_str[i]))
				insert_token_before(tokens, token_after_exp,
					whitespace_token(token_str, &i, &type), &type);
			else
				insert_token_before(tokens, token_after_exp,
					word_token(token_str, &i, &type), &type);
		}
		ft_lstremove(tokens, node, token_del);
	}
	return (*tokens);
}

/**
 * example: ech"o"
 * initially this would be recognized  as two tokens by the parser
 * however they are merged to one token
 * merging happens when the previous token of a WORD token is also
 * a WORD token 
*/
t_list	*merge_words(t_list **tokens, t_list *node)
{
	t_list	*prev;
	char	*new_token_str;

	if (((t_token *)node->content)->type == WORD)
	{
		prev = ft_lstfindprev(*tokens, node);
		if (prev && ((t_token *)prev->content)->type == WORD)
		{
			new_token_str = ft_strjoin(((t_token *)prev->content)->str,
					((t_token *)node->content)->str);
			free(((t_token *)prev->content)->str);
			((t_token *)prev->content)->str = new_token_str;
			ft_lstremove(tokens, node, token_del);
		}
	}
	return (*tokens);
}

/**
 * remove all whitespace tokens before handing ob the token list
 * to the parser
 * whitespace tokens where used for word_splitting in parameter
 * expansion
*/
t_list	*remove_whitespace(t_list **tokens, t_list *node)
{
	if (((t_token *)node->content)->type == WHITESPACE)
		ft_lstremove(tokens, node, token_del);
	return (*tokens);
}
