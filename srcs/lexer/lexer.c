/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:23:20 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/05 10:37:52 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

/**
 * command line gets split into tokens. tokens are either words or operators
 * metacharacters are used as separators for splitting (only when unquoted): 
 * ' ', '\t', '\n', '|', '>', '<'
 * 
 * -> function when quote is recognized
*/	
t_list	*scan_tokens(char *line, t_data *data)
{
	size_t			i;
	e_token_types	type;
	t_list			*tokens;
	char			*token_str;

	i = 0;
	tokens = NULL;
	while (line && line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			token_str = redirection_token(line, &i, &type);
		else if (line[i] == '$')
			token_str = parameter_token(line, &i, &type, data->envp);
		else if (line[i] == '\'' || line[i] == '\"')
			token_str = quote_token(line, &i, &type, data->envp);
		else if (is_whitespace(line[i]))
			token_str = whitespace_token(line, &i, &type);
		else if (line[i] == '|')
			token_str = pipe_token(line, &i, &type);
		else
			token_str = word_token(line, &i, &type);
		tokens = save_token(&tokens, token_str, type);
	}
	tokens = modify_list(&tokens, word_splitting);
	tokens = modify_list(&tokens, merge_words);
	tokens = modify_list(&tokens, remove_whitespace);
	return (tokens);
}
