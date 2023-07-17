/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_token_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:05:14 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/17 16:07:51 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

/**
 * save everything until the next metacharacter or quote a a WORD token
*/
char	*word_token(char *line, size_t *i, t_token_types *type)
{
	size_t	token_begin;

	token_begin = *i;
	*type = WORD;
	while (!is_metacharacter(line[*i]) && !is_quote(line[*i]) && line[*i]
			&& line[*i] != '$')
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

/**
 * allocate memory (assign_token_attr) for new token node and insert
 * it in the back of token linked list
 * 
*/
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

/**
 * allcoates memory for a new token node and assigns attributes
 * token_str and type and inserts it in the token linked_list
 * before the token_prepended
*/
void	insert_token_before(t_list **tokens, t_list *token_prepended,
		char *token_str, t_token_types *type)
{
	t_list	*new_token;
	t_token	*token_data;

	token_data = assign_token_attr(token_str, *type);
	new_token = ft_lstnew(token_data);
	ft_lst_insert_before(tokens, token_prepended, new_token);
}
