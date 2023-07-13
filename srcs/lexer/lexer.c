/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:23:20 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/11 11:36:29 by aehrlich         ###   ########.fr       */
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
	t_token_types	type;
	t_list			*tokens;
	char			*token_str;

	i = 0;
	tokens = NULL;
	while (line && line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			token_str = redirection_token(line, &i, &type);
		else if (line[i] == '$')
			token_str = parameter_token(line, &i, &type, data->env_dict);
		else if (line[i] == '\'' || line[i] == '\"')
			token_str = quote_token(line, &i, &type, data->env_dict);
		else if (is_whitespace(line[i]))
			token_str = whitespace_token(line, &i, &type);
		else if (line[i] == '|')
			token_str = pipe_token(&i, &type);
		else
			token_str = word_token(line, &i, &type);
		tokens = save_token(&tokens, token_str, type);
	}
	return (tokens_postprocess(tokens));
}

/**
 * print e_token_type to standard output for debugging purposes
*/
void	print_t_token_types(t_token_types type)
{
	if (type == O_RED)
		printf("O_RED\n");
	else if (type == I_RED)
		printf("I_RED\n");
	else if (type == I_RED)
		printf("I_RED\n");
	else if (type == I_RED_HD)
		printf("I_RED_HD\n");
	else if (type == O_RED_APP)
		printf("O_RED_APP\n");
	else if (type == EQUALS)
		printf("EQUALS\n");
	else if (type == PIPE)
		printf("PIPE\n");
	else if (type == WORD)
		printf("WORD\n");
	else if (type == DQUOTES)
		printf("DQUOTES\n");
	else if (type == SQUOTES)
		printf("SQUOTES\n");
	else if (type == PARAMETER)
		printf("PARAMETER\n");
	else if (type == WHITESPACE)
		printf("WHITESPACE\n");
}

/**
 * print token_type and token_str to standard output for debugging purposes
 * output format: [<token_str>] <token_type>
*/
void	print_token(void *arg)
{
	printf("%s\t", ((t_token *)arg)->str);
	print_t_token_types(((t_token *)arg)->type);
}

/**
 * frees the token_str and the allocated token struct -> should be passed as
 * delete function to ft_lstclear
 * freed pointers are set to NULL to avoid double freeing
*/
void	token_del(void *arg)
{
	t_token	*token_data;

	if (!arg)
		return ;
	token_data = (t_token *)arg;
	if (!token_data)
		return ;
	token_data->str = ft_free_set_null(token_data->str);
	token_data = ft_free_set_null(token_data);
}
