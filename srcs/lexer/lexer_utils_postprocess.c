/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_postprocess.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:10:21 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/09 12:20:48 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

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

t_list	*word_splitting(t_list **tokens, t_list *node)
{
	char			*token_str;
	t_list			*token_after_exp;
	e_token_types	type;
	size_t			i;
	
	if (((t_token *)node->content)->type == PARAMETER)
	{
		token_str = ((t_token *)node->content)->str;
		i = 0;
		token_after_exp = node->next;
		while (token_str[i])
		{
			if (is_whitespace(token_str[i]))
				insert_token_before(tokens, token_after_exp, whitespace_token(token_str, &i, &type), type);
			else
				insert_token_before(tokens, token_after_exp, word_token(token_str, &i, &type), type);
		}
		ft_lstremove(tokens, node, token_del);
	}
	return (*tokens);
}

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

t_list	*remove_whitespace(t_list **tokens, t_list *node)
{

	if (((t_token *)node->content)->type == WHITESPACE)
		ft_lstremove(tokens, node, token_del);
	return (*tokens);
}
