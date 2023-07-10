/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:08:41 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/10 14:12:40 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

/*
	A builtin can either be executed in the main process when standing alone or
	as a child when it appears in a pipeline. In the main process the return value
	should not break the readline loop, therefore different exit values are 
	necessary. 
*/
int	execute_builtin_cmd(t_data *data, t_command *command)
{
	char	**arg_arr;
	int		exit_code;

	arg_arr = ft_lst_strarr(command->arguments);
	if (ft_strcmp((const char *)arg_arr[0], "echo") == 0)
		exit_code = builtin_echo((const char **)arg_arr);
	if (ft_strcmp((const char *)arg_arr[0], "cd") == 0)
		exit_code = builtin_cd((const char **)arg_arr, data->env_dict);
	if (ft_strcmp((const char *)arg_arr[0], "pwd") == 0)
		exit_code = builtin_pwd();
	if (ft_strcmp((const char *)arg_arr[0], "env") == 0)
		exit_code = builtin_env(data->env_dict);
	if (ft_strcmp((const char *)arg_arr[0], "exit") == 0)
		exit_code = builtin_exit((const char **)arg_arr, data);
	if (ft_strcmp((const char *)arg_arr[0], "export") == 0)
		exit_code = builtin_export((const char **)arg_arr, data->env_dict);
	if (ft_strcmp((const char *)arg_arr[0], "unset") == 0)
		exit_code = builtin_unset((const char **)arg_arr, data);
	arg_arr = ft_free_split_arr(arg_arr);
	return (exit_code);
}
