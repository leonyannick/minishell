/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:27:55 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/10 15:37:36 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

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
			return (NULL); //TODO: Free the list array until here
		*str_arr = temp_str;
		str_arr++;
		list = list->next;
	}
	*str_arr = NULL;
	return (ret_arr);
}
