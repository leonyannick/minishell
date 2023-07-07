/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:22:05 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/07 10:18:25 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

void	builtin_unset(const char **argv, t_list *env_dict)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		ft_dict_rm_node(&env_dict, (char *)argv[i]);
		i++;
	}
}
/* TEST DUMP
t_list *dict;
	dict = ft_dict_from_strarr(environ);
	const char **argv_test;

	ft_lstiter(dict, ft_dict_print);
	argv_test = malloc(sizeof(char *) * 3);
	argv_test[0] = ft_strdup("unset");
	argv_test[1] = ft_strdup("HOME");
	argv_test[2] = NULL;
	builtin_unset(argv_test, dict);
	printf("\n\n\n\n");
	ft_lstiter(dict, ft_dict_print);
	
	
	ft_lstclear(&dict, ft_dict_node_del);
	free(argv_test);
*/
