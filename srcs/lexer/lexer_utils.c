/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:38:03 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/02 14:33:01 by lbaumann         ###   ########.fr       */
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

t_list	*save_token(t_list **tokens, char *token_str, e_token_types type)
{
	t_list *new_token;
	t_token	*token_data;

	token_data = assign_token_attr(token_str, type);
	new_token = ft_lstnew(token_data);
	ft_lstadd_back(tokens, new_token);
	return (*tokens);
}

bool	is_red_operator(char c)
{
	if (c == '<' || c == '>')
		return (true);
	else
		return (false);
}

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

char	*expand(char *line, size_t *i, char **envp)
{
	envp = NULL;
	if (!line[*i] || line[*i] == '"')
		return (ft_strdup(""));
	while (!is_metacharacter(line[*i]) && !is_quote(line[*i]) && line[*i])
		(*i)++;
	//expand(*i - token_begin)
	return (ft_strdup("REPLAC EMENT"));
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

char	*char_to_str(char c)
{
	char	*result;

	result = ft_calloc(2, sizeof(char));
	if (!result)
		return (NULL);
	result[0] = c;
	return (result);
}

char	*append_str(char *str, char *appendix)
{
	char	*junction;

	if (!str)
		return (appendix);
	junction = ft_strjoin(str, appendix);
	free(str);
	free(appendix);
	return (junction);
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

char	*word_token(char *line, size_t *i, e_token_types *type)
{
	size_t	token_begin;

	token_begin = *i;
	*type = WORD;
	while (!is_metacharacter(line[*i]) && !is_quote(line[*i]) && line[*i])
		(*i)++;
	return (ft_substr(line, token_begin, *i - token_begin));
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

void	skip_whitespace(char *str, size_t *i)
{
	while (is_whitespace(str[*i]) && str[*i])
		(*i)++;
}

void	insert_token(t_list *tokens, t_list *old, char *token_str, e_token_types type)
{
	t_list *new_token;
	t_token	*token_data;

	token_data = assign_token_attr(token_str, type);
	new_token = ft_lstnew(token_data);
	ft_lstadd_insert(tokens, old, new_token);
}

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
