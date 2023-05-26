/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:38:03 by lbaumann          #+#    #+#             */
/*   Updated: 2023/05/26 16:07:31 by lbaumann         ###   ########.fr       */
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

void	save_token(t_list *head, char *token_begin, size_t token_length, e_token_types type)
{
	char *token_str;
	t_list *new_token;
	t_token	*token_data;

	token_str = ft_substr(token_begin, 0, token_length);
	token_data = assign_token_attr(token_str, type);
	new_token = ft_lstnew(token_data);
	ft_lstadd_back(&head, new_token);
}

bool	is_red_operator(char c)
{
	if (c == '<' || c == '>')
		return (true);
	else
		return (false);
}

size_t	save_redirection_token(t_list *head, char *token_begin)
{
	if (token_begin[0] == '<' && !is_operator(token_begin[1]))
	{
		save_token(head, token_begin, 1, I_RED);
		return (1);
	}
	else if (token_begin[0] == '>' && !is_operator(token_begin[1]))
	{
		save_token(head, token_begin, 1, O_RED);
		return (1);
	}
	else if (!ft_strncmp(token_begin, "<<", 2) && !is_operator(token_begin[2]))
	{
		save_token(head, token_begin, 2, I_RED_HD);
		return (2);
	}
	else if (!ft_strncmp(token_begin, ">>", 2) && !is_operator(token_begin[2]))
	{
		save_token(head, token_begin, 2, O_RED_APP);
		return (2);
	}
	printf("syntax error near unexpected token\n");
	return (0);
}

char	*expand(char *to_be_expanded)
{
	size_t	token_length;
	char	*replacement;

	token_length = 0;
	while (!is_metacharacter(to_be_expanded[token_length]) && to_be_expanded[token_length])
		token_length++;
	replacement = ft_strdup("PLACE HOLDER");
	return (ft_strjoin(replacement, &to_be_expanded[token_length]));
}

/**
 * increase token_begin by one to omit the $, the info is saved as the token_type anyways
*/
size_t	save_parameter_token(t_list *head, char *token_begin)
{
	size_t	token_length;

	token_begin++;
	token_length = 0;
	while (!is_metacharacter(token_begin[token_length]) && token_begin[token_length])
		token_length++;
	token_begin = expand(token_begin);
	save_token(head, token_begin, ft_strlen(token_begin), PARAMETER);
	return (token_length + 1);
}

size_t	save_quote_token(t_list *head, char *token_begin)
{
	size_t			token_length;

	token_length = 0;
	if (token_begin[0] == '\'')
	{
		token_begin++;
		while (token_begin[token_length] != '\'' && token_begin[token_length])
			token_length++;
		save_token(head, token_begin, token_length, SQUOTES);
	}
	else
	{
		token_begin++;
		while (token_begin[token_length] != '\"' && token_begin[token_length])
		{
			if (token_begin[token_length] == '$')
			{
				token_begin[token_length] = expand(&token_begin[token_length]);
				token_length += ft_strlen(token_begin);
			}
			else
				token_length++;
		}
		save_token(head, token_begin, token_length, DQUOTES);
	}
	return (token_length + 2);
}

size_t	save_word_token(t_list *head, char *token_begin)
{
	size_t	token_length;

	token_length = 0;
	while (!is_metacharacter(token_begin[token_length]) && token_begin[token_length])
		token_length++;
	save_token(head, token_begin, token_length, WORD);
	return (token_length);
}

size_t	skip_whitespace(t_list *head, char *token_begin)
{
	size_t	token_length;

	token_length = 0;
	while (is_whitespace(token_begin[token_length]) && token_begin[token_length])
		token_length++;
	save_token(head, token_begin, token_length, WHITESPACE);
	return (token_length);
}

size_t	save_pipe_token(t_list *head, char *token_begin)
{
	if (token_begin[0] == '|' && !is_operator(token_begin[1]))
	{
		save_token(head, token_begin, 1, PIPE);
		return (1);
	}
	printf("syntax error near unexpected token\n");
	return (0);
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
	size_t	i;

	head = ft_lstnew(NULL);
	i = 0;
	while (line && line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			i += save_redirection_token(head, &line[i]);//detect what redirection operator there is << >> < >
		else if (line[i] == '$')
			i += save_parameter_token(head, &line[i]);
		else if (line[i] == '\'' || line[i] == '\"')
			i += save_quote_token(head, &line[i]);
		else if (is_whitespace(line[i]))
			i += skip_whitespace(head, &line[i]);
		else if (line[i] == '|')
			i += save_pipe_token(head, &line[i]);
		else
			i += save_word_token(head, &line[i]);
	}
	temp = head->next;
	ft_lstdelone(head, free);
	return (temp);
}
