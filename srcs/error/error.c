/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/18 10:54:10 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/error.h"

/**
 * call this function to report an error on the standard output 
 * either errno is returned or if given, a custom error code
 * -> minishell is not terminated (while loop is continued)
 * perror is used to print the err_description when the param
 * cstm_err_descr is NULL
 * 
 * example: "usheless: cd: too many arguments"
 * "cd": err_origin
 * "too many arguments": cstm_err_description
*/
int	error_continue(const char *err_origin, const char *err_object,
	const char *cstm_err_descr, int cstm_exit_code)
{
	ft_fd_printf(STDERR_FILENO, "ushelless: ");
	if (err_origin)
		ft_fd_printf(STDERR_FILENO, "%s: ", err_origin);
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
