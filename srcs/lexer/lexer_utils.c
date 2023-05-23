/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:38:03 by lbaumann          #+#    #+#             */
/*   Updated: 2023/05/23 20:28:04 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*assignTokenAttr(char *tokenStr)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->tokenStr = tokenStr;
	return (token);
}

/**
 * command line gets split into tokens. tokens are either words or operators
 * metacharacters are used as separators for splitting (only when unquoted): 
 * ' ', '\t', '\n', '|', '>', '<'
 * 
 * -> function when quote is recognized
*/	
t_list	*getTokens(char *line)
{
	t_list	*head;
	char	**splitLine;
	int		i;

	splitLine = ft_split(line, ' ');
	i = 0;
	while (splitLine[i])
	{
		if (i == 0)
			head = ft_lstnew(assignTokenAttr(splitLine[i]));
		else
			ft_lstadd_back(&head, ft_lstnew(assignTokenAttr(splitLine[i])));
		i++;
	}
	return (head);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
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


// char	*tokenBegin;
// 	char	*forward;
// 	int		i;

// 	i = 0;
// 	head = NULL;
// 	tokenBegin = line;
// 	forward = line;
// 	while (forward)
// 	{
// 		if (is_metacharacter(*forward))
// 		{
// 			saveToken(head, tokenBegin, forward);
// 			tokenBegin = forward;
// 		}
// 		forward++;
// 	}
