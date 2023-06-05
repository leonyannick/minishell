/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_helper_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:09:27 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/05 10:09:57 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

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
