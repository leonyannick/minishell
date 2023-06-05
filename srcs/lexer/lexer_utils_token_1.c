/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_tokentype_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:03:20 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/05 10:05:40 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

char	*redirection_token(char *line, size_t *i, e_token_types *type)
{
	if (line[*i] == '<' && !is_operator(line[*i + 1]))
	{
		(*i)++;
		*type = I_RED;
		return (ft_strdup("<"));
	}
	else if (line[*i] == '>' && !is_operator(line[*i + 1]))
	{
		(*i)++;
		*type = O_RED;
		return (ft_strdup(">"));
	}
	else if (!ft_strncmp(&line[*i], "<<", 2) && !is_operator(line[*i + 2]))
	{
		*i += 2;
		*type = I_RED_HD;
		return (ft_strdup("<<"));
	}
	else if (!ft_strncmp(&line[*i], ">>", 2) && !is_operator(line[*i + 2]))
	{
		*i += 2;
		*type = O_RED_APP;
		return (ft_strdup(">>"));
	}
	printf("syntax error near unexpected token\n");
	return (0);
}

/**
 * increase token_begin by one to omit the $, the info is saved as the token_type anyways
*/
char	*parameter_token(char *line, size_t *i, e_token_types *type, char **envp)
{
	(*i)++;
	*type = PARAMETER;
	return (expand(line, i, envp));
}

char	*quote_token(char *line, size_t *i, e_token_types *type, char **envp)
{
	char	*token_str;
	char	*expansion;

	token_str = NULL;
	if (line[(*i)++] == '"')
		*type = DQUOTES;
	else
		*type = SQUOTES;
	while (*type == SQUOTES && line[*i] != '\'' && line[*i])
		token_str = append_str(token_str, char_to_str(line[(*i)++]));
	while (*type == DQUOTES && line[*i] != '"' && line[*i])
	{
		if (line[(*i)] == '$')
		{
			(*i)++;
			expansion = expand(line, i, envp);
			token_str = append_str(token_str, expansion);
		}
		else
			token_str = append_str(token_str, char_to_str(line[(*i)++]));
	}
	(*i)++;
	*type = WORD;
	return (token_str);
}

char	*whitespace_token(char *line, size_t *i, e_token_types *type)
{
	size_t	token_begin;

	token_begin = *i;
	*type = WHITESPACE;
	while (is_whitespace(line[*i]) && line[*i])
		(*i)++;
	return (ft_substr(line, token_begin, *i - token_begin));
}

char	*pipe_token(char *line, size_t *i, e_token_types *type)
{
	*type = PIPE;
	if (line[*i] == '|' && !is_operator(line[*i + 1]))
	{
		(*i)++;
		return (ft_strdup("|"));
	}
	printf("syntax error near unexpected token\n");
	return (0);
}
