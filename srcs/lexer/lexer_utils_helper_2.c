/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_helper_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:09:27 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/18 09:50:21 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

/**
 * if end of line is reached or double quote -> expand returns an allocated <$>
 * line is parsed until end of quote or metacharacter is found
 * the var_name substring is allocated from the parsed line and the env_dict
 * is searched for an entry with that key
 * var_name is freed after the dictionary has been searched
 * strdup of var_value is returned from the expand function (because it will
 * be freed by lexer later)
*/
char	*expand(char *line, size_t *i, t_list *env_dict)
{
	size_t	token_begin;
	char	*var_name;
	char	*var_value;

	token_begin = *i;
	if (!line[*i] || line[*i] == '"')
		return (ft_strdup("$"));
	if (line[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_exit_code));
	}
	while (!is_metacharacter(line[*i]) && !is_quote(line[*i])
		&& line[*i] != '$' && line[*i])
		(*i)++;
	var_name = ft_substr(line, token_begin, *i - token_begin);
	var_value = ft_dict_get_value(env_dict, var_name);
	free(var_name);
	return (ft_strdup(var_value));
}

/**
 * return a NULL-terminated allocated string from char c
*/
char	*char_to_str(char c)
{
	char	*result;

	result = ft_calloc(2, sizeof(char));
	if (!result)
		return (NULL);
	result[0] = c;
	return (result);
}

/**
 * append str with the appendix and return the new
 * concatonated version. both the old str and the appendix
 * are freed
*/
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
