/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_token_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:05:14 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/11 11:36:29 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

char	*word_token(char *line, size_t *i, t_token_types *type)
{
	size_t	token_begin;

	token_begin = *i;
	*type = WORD;
	while (!is_metacharacter(line[*i]) && !is_quote(line[*i]) && line[*i])
		(*i)++;
	return (ft_substr(line, token_begin, *i - token_begin));
}

/**
 * assigns the token attributes (str and type)
 * 
 * if token_str is null pointer, allocate an empty str to prevent
 * segfaults with library functions
*/
t_token	*assign_token_attr(char *token_str, t_token_types type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (!token_str)
		token_str = ft_strdup("");
	token->str = token_str;
	if (!token_str)
		return (NULL);
	token->type = type;
	return (token);
}

t_list	*save_token(t_list **tokens, char *token_str, t_token_types type)
{
	t_list	*new_token;
	t_token	*token_data;

	token_data = assign_token_attr(token_str, type);
	if (!token_data)
		return (NULL);
	new_token = ft_lstnew(token_data);
	ft_lstadd_back(tokens, new_token);
	return (*tokens);
}

void	insert_token_before(t_list **tokens, t_list *token_prepended,
		char *token_str, t_token_types type)
{
	t_list	*new_token;
	t_token	*token_data;

	token_data = assign_token_attr(token_str, type);
	new_token = ft_lstnew(token_data);
	ft_lst_insert_before(tokens, token_prepended, new_token);
}
