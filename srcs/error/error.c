/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:32:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/05/25 10:42:57 by lbaumann         ###   ########.fr       */
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
 * -> minishell is not terminated
*/
void	error_soft(char *error_msg, void *mem)
{
	mem = NULL; //memory management has to be implemented
	perror(error_msg);
}
