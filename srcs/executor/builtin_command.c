/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:08:41 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/27 18:09:07 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

/*
	A builtin can either be executed in the main process when standing alone or
	as a child when it appears in a pipeline. In the main process the return value
	should not break the readline loop, therefore different exit values are 
	necessary. 
*/
int	exeute_builtin_cmd(t_data *data, t_command *command, int exit_type)
{
	if (!data || !command)
		return (-1);
	printf("BUILTIN\n");
	return (exit_type);
}
