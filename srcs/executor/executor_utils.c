/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:27:55 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/13 17:08:04 by aehrlich         ###   ########.fr       */
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
