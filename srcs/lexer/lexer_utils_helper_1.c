/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_helper_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:08:24 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/07 16:20:05 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else
		return (false);
}

bool	is_quote(char c)
{
	if (c == '"' || c == '\'')
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

void	skip_whitespace(char *str, size_t *i)
{
	while (is_whitespace(str[*i]) && str[*i])
		(*i)++;
}
