/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:08:41 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/28 10:23:43 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

/*
	A builtin can either be executed in the main process when standing alone or
	as a child when it appears in a pipeline. In the main process the return value
	should not break the readline loop, therefore different exit values are 
	necessary. 
*/
int	exeute_builtin_cmd(t_command *command, int exit_type)
{
	char	**arg_arr;
	t_list	*dict;

	arg_arr = ft_lst_strarr(command->arguments);
	dict = ft_dict_from_strarr(arg_arr);
	if (ft_strcmp((const char *)arg_arr[0], "echo") == 0)
		builtin_echo((const char **)arg_arr);
	if (ft_strcmp((const char *)arg_arr[0], "cd") == 0)
		builtin_cd((const char **)arg_arr, dict);
	if (ft_strcmp((const char *)arg_arr[0], "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp((const char *)arg_arr[0], "env") == 0)
		builtin_env(dict);
	if (ft_strcmp((const char *)arg_arr[0], "exit") == 0)
		builtin_exit((const char **)arg_arr);
	if (ft_strcmp((const char *)arg_arr[0], "export") == 0)
		builtin_export((const char **)arg_arr, dict);
	if (ft_strcmp((const char *)arg_arr[0], "unset") == 0)
		builtin_unset((const char **)arg_arr, dict);
	ft_lstclear(&dict, ft_dict_node_del);
	arg_arr = ft_free_split_arr(arg_arr);
	return (exit_type);
}
