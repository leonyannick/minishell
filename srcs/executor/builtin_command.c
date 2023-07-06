/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:08:41 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/06 12:14:50 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

/*
	A builtin can either be executed in the main process when standing alone or
	as a child when it appears in a pipeline. In the main process the return value
	should not break the readline loop, therefore different exit values are 
	necessary. 
*/
int	execute_builtin_cmd(t_data *data, t_command *command, int exit_type)
{
	char	**arg_arr;

	arg_arr = ft_lst_strarr(command->arguments);
	if (ft_strcmp((const char *)arg_arr[0], "echo") == 0)
		builtin_echo((const char **)arg_arr);
	if (ft_strcmp((const char *)arg_arr[0], "cd") == 0)
		builtin_cd((const char **)arg_arr, data->env_dict);
	if (ft_strcmp((const char *)arg_arr[0], "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp((const char *)arg_arr[0], "env") == 0)
		builtin_env(data->env_dict);
	if (ft_strcmp((const char *)arg_arr[0], "exit") == 0)
		builtin_exit((const char **)arg_arr);
	if (ft_strcmp((const char *)arg_arr[0], "export") == 0)
		builtin_export((const char **)arg_arr, data->env_dict);
	if (ft_strcmp((const char *)arg_arr[0], "unset") == 0)
		builtin_unset((const char **)arg_arr, data->env_dict);
	arg_arr = ft_free_split_arr(arg_arr);
	return (exit_type);
}
