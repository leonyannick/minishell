/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:27:55 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/12 12:25:08 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

/* 
	converts a linked list of strings into a NULL-terminated array of strings
	and returns it.
	@argument - list:	list to convert
	@return:			NULL-terminated array of strings
 */
char	**ft_lst_strarr(t_list *list)
{
	char	**str_arr;
	char	**ret_arr;
	char	*temp_str;

	str_arr = malloc((ft_lstsize(list) + 1) * sizeof(char *));
	if (!str_arr)
		return (NULL);
	ret_arr = str_arr;
	while (list)
	{
		temp_str = ft_strdup((char *)list->content);
		if (!temp_str)
			return (NULL);
		*str_arr = temp_str;
		str_arr++;
		list = list->next;
	}
	*str_arr = NULL;
	return (ret_arr);
}

/*
	checks if the end of a passed arg is "minishell", if the passed string
	is shorter, false is returned. If the last part of the string is
	"minishell", true is returned.
*/
bool	is_minishell_called(t_data *data, t_command *cmd)
{
	int		len;
	int		offset;
	char	*path;

	if (!cmd->arguments)
		return (false);
	path = (char *)cmd->arguments->content;
	len = ft_strlen(path);
	offset = ft_strlen(path) - ft_strlen("minishell");
	if (offset < 0)
		return (false);
	if (ft_strcmp("minishell", path + offset) == 0)
	{
		data->is_child_minishell = true;
		return (true);
	}
	return (false);
}
