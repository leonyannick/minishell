/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:32:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/11 12:44:08 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"

/**
 * call this function when error occurrs that makes continuing running
 * minishell impossible -> minishell will be terminated
 * @param error_msg message for perror that reports where the error occurred
 * @param mem pointer to memory that should be freed before exiting
*/
void	error_fatal(char *error_msg, void *mem)
{
	mem = NULL; //memory management has to be implemented
	perror(error_msg);
	exit(errno);
}

/**
 * call this function to report an error on the standard output 
 * and set the exit_code to errno
 * -> minishell is not terminated (while loop is continued)
*/
int	error_continue(const char *err_origin, const char *err_object,
	const char *cstm_err_descr, int cstm_exit_code)
{
	ft_fd_printf(STDERR_FILENO, "ushelless: %s: ", err_origin);
	if (err_object)
		ft_fd_printf(STDERR_FILENO, "%s: ", err_object);
	if (cstm_err_descr)
		ft_fd_printf(STDERR_FILENO, "%s\n", cstm_err_descr);
	if (cstm_exit_code)
		return (cstm_exit_code);
	else
	{
		perror("");
		return (errno);
	}
}
