/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:38:03 by lbaumann          #+#    #+#             */
/*   Updated: 2023/05/24 16:51:43 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else
		return (false);
}

bool	is_metacharacter(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\n' || c == '|'
		|| c == '<' || c == '>')
		return (true);
	else
		return (false);
}

bool	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

t_token	*assign_token_attr(char *token_str, e_token_types type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->token_str = token_str;
	token->token_type = type;
	return (token);
}

bool	is_red_operator(char c)
{
	if (c == '<' || c == '>')
		return (true);
	else
		return (false);
}

char	*save_redirection_token(t_list *head, char *token_begin)
{
	if (token_begin[0] == '<' && !is_operator(token_begin[1]))
	{
		ft_lstadd_back(&head,
			ft_lstnew(assign_token_attr(ft_strdup("<"), I_RED)));
		return (&token_begin[1]);
	}
	else if (token_begin[0] == '>' && !is_operator(token_begin[1]))
	{
		ft_lstadd_back(&head,
			ft_lstnew(assign_token_attr(ft_strdup(">"), O_RED)));
		return (&token_begin[1]);
	}
	else if (!ft_strncmp(token_begin, "<<", 2) && !is_operator(token_begin[2]))
	{
		ft_lstadd_back(&head,
			ft_lstnew(assign_token_attr(ft_strdup("<<"), I_RED_HD)));
		return (&token_begin[2]);
	}
	else if (!ft_strncmp(token_begin, ">>", 2) && !is_operator(token_begin[2]))
	{
		ft_lstadd_back(&head,
			ft_lstnew(assign_token_attr(ft_strdup(">>"), O_RED_APP)));
		return (&token_begin[2]);
	}
	printf("syntax error near unexpected token\n");
	return (NULL);
}

// /**
//  * increase token_begin by one to omit the $, the info is saved as the token_type anyways
// */
// char	*save_parameter_token(t_list *head, char *token_begin)
// {
// 	size_t	token_length;
// 	char	*token_str;

// 	token_begin++;
// 	token_length = 0;
// 	while (!is_metacharacter(token_begin[token_length]) && token_begin[token_length])
// 		token_length++;
// 	token_str = ft_substr(token_begin, 0, token_length);
// 	ft_lstadd_back(&head, ft_lstnew(assign_token_attr(token_str, PARAMETER)));
// 	return (&token_begin[token_length]);
// }

char	*save_quote_token(t_list *head, char *token_begin)
{
	e_token_types	type;
	size_t			token_length;
	char	*		token_str;

	token_length = 0;
	if (*token_begin == '\'')
	{
		token_begin++;
		while (token_begin[token_length] != '\'' && token_begin[token_length])
			token_length++;
		type = SQUOTES;
	}
	else
	{
		token_begin++;
		while (token_begin[token_length] != '\"' && token_begin[token_length])
			token_length++;
		type = DQUOTES;
	}
	token_str = ft_substr(token_begin, 0, token_length);
	ft_lstadd_back(&head, ft_lstnew(assign_token_attr(token_str, type)));
	return (&token_begin[++token_length]);
}

char	*save_word_token(t_list *head, char *token_begin)
{
	size_t	token_length;
	char	*token_str;

	token_length = 0;
	while (!is_metacharacter(token_begin[token_length]) && token_begin[token_length])
		token_length++;
	token_str = ft_substr(token_begin, 0, token_length);
	ft_lstadd_back(&head, ft_lstnew(assign_token_attr(token_str, WORD)));
	return (&token_begin[token_length]);
}

char	*skip_whitespace(char *token_begin)
{
	size_t	token_length;

	token_length = 0;
	while (is_whitespace(token_begin[token_length]) && token_begin[token_length])
		token_length++;
	return (&token_begin[token_length]);
}

char	*save_pipe_token(t_list *head, char *token_begin)
{
	if (token_begin[0] == '|' && !is_operator(token_begin[1]))
	{
		ft_lstadd_back(&head, ft_lstnew(assign_token_attr(ft_strdup("|"), PIPE)));
		return &token_begin[1];
	}
	printf("syntax error near unexpected token\n");
	return (NULL);
}

/**
 * command line gets split into tokens. tokens are either words or operators
 * metacharacters are used as separators for splitting (only when unquoted): 
 * ' ', '\t', '\n', '|', '>', '<'
 * 
 * -> function when quote is recognized
*/	
t_list	*scan_tokens(char *line)
{
	t_list	*head;
	t_list	*temp;

	head = ft_lstnew(NULL);
	while (line && *line)
	{
		if (*line == '<' || *line == '>')
			line = save_redirection_token(head, line);//detect what redirection operator there is << >> < >
		// else if (*line == '$')
		// 	line = save_parameter_token(head, line);
		else if (*line == '\'' || *line == '\"')
			line = save_quote_token(head, line);
		else if (is_whitespace(*line))
			line = skip_whitespace(line);
		else if (*line == '|')
			line = save_pipe_token(head, line);
		else
			line = save_word_token(head, line);
	}
	temp = head->next;
	ft_lstdelone(head, free);
	return (temp);
}
