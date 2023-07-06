/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:51:49 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/06 12:03:37 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

/**
 * return NULL if no '=' is found in arg str
 * key = key_val[0]
 * value = key_val[1]
 * equals is a pointer to the first occurrence of '='
*/
static char	**split_key_val(const char *arg, char **key_val)
{
	char	*equals;
	size_t	len;

	equals = ft_strchr(arg, '=');
	if (!equals || !key_val)
		return (NULL);
	len = ft_strlen(arg);
	key_val[0] = ft_substr(arg, 0, equals - arg);
	key_val[1] = ft_substr(equals + 1, 0, &arg[len] - equals);
	return (key_val);
}

/**
 * key_val[0] = key
 * key_val[1] = val
 * both are allocated in split_key_val
 * the key needs to be freed after ft_dict_add_node, because it is newly
 * allocated there
*/
void	builtin_export(const char **argv, t_list *env_dict)
{
	size_t	i;
	char *key_val[2];
	
	i = 1;
	while(argv[i])
	{
		if (split_key_val(argv[i], key_val))
		{
			ft_dict_add_node(&env_dict, key_val[0], key_val[1]);
			key_val[0] = ft_free_set_null(key_val[0]);
		}
		i++;
	}
}

/* TEST DUMP
t_list	*dict;
	// char	**arr;

	dict = ft_dict_from_strarr(environ);
	const char **argv_test;

	argv_test = malloc(sizeof(char *) * 3);
	argv_test[0] = ft_strdup("export");
	argv_test[1] = ft_strdup("var2");
	argv_test[2] = NULL;
	// char	*str = ft_strdup("");
	// ft_dict_add_node(&dict, "sehr", str);
	// ft_lstiter(dict, ft_dict_print);
	builtin_export(argv_test, dict);
	ft_lstiter(dict, ft_dict_print);
	char **envp_test = ft_dict_to_strarr(dict);
	print_string_arr(envp_test);
	ft_free_split_arr(envp_test);
	ft_lstclear(&dict, ft_dict_node_del);
	free(argv_test);
	// arr = dict_to_strarr(dict);
	// print_string_arr(arr);
	// ft_lstclear(&dict, ft_dict_node_del);
	// const char arg[] = "val===6";
	// char *key_val[2];
	// if(!split_key_val(arg, key_val))
	// 	printf("no equals\n");
	// printf("key: %s\n", key_val[0]);
	// printf("value: %s\n", key_val[1]);
*/
