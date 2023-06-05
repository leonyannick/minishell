/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_postprocess.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:10:21 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/05 10:10:57 by lbaumann         ###   ########.fr       */
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
	t_list			*temp;
	e_token_types	type;
	size_t			i;
	
	if (((t_token *)node->content)->token_type == PARAMETER)
	{
		token_str = ((t_token *)node->content)->token_str;
		i = 0;
		temp = node->next;
		while (token_str[i])
		{
			if (is_whitespace(token_str[i]))
				insert_token(*tokens, temp, whitespace_token(token_str, &i, &type), type);
			else
				insert_token(*tokens, temp, word_token(token_str, &i, &type), type);
		}
		ft_lstremove(tokens, node);
	}
	return (*tokens);
}

t_list	*merge_words(t_list **tokens, t_list *node)
{
	t_list	*prev;
	char	*new_token_str;

	// ft_lstiter(*tokens, print_token);
	if (((t_token *)node->content)->token_type == WORD)
	{
		prev = ft_lstfindprev(*tokens, node);
		if (prev && ((t_token *)prev->content)->token_type == WORD)
		{
			new_token_str = ft_strjoin(((t_token *)prev->content)->token_str,
			((t_token *)node->content)->token_str);
			free(((t_token *)prev->content)->token_str);
			((t_token *)prev->content)->token_str = new_token_str;
			ft_lstremove(tokens, node);
		}
	}
	return (*tokens);
}

t_list	*remove_whitespace(t_list **tokens, t_list *node)
{

	if (((t_token *)node->content)->token_type == WHITESPACE)
		ft_lstremove(tokens, node);
	return (*tokens);
}
