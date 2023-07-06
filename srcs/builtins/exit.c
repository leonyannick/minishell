/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:39:50 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/06 18:56:05 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

/**
 * return unsigned char 0-255
 * why do I even try to mimic the behaviour of bash???!!
 * numeric argument required has higher precedence than too many args
 * too many args does not exit the shell
 * exit is printed out even if the shell is not exited
 * numeric argument exit code: 2
 * exit without args exit code: 0
*/
void	builtin_exit(const char **argv)
{
	unsigned char	ret;
	int				argc;

	printf("exit\n");
	argc = ft_argc_from_argv(argv);
	ret = EXIT_SUCCESS;
	if (argc != 1 && !ft_is_str_nbr(argv[1]))
	{
		ft_fd_printf(STDERR_FILENO,
			"ushelless: exit: %s: numeric argument required\n", argv[1]);
		ret = 2;
	}
	else if (argc > 2)
	{
		ft_fd_printf(STDERR_FILENO, "ushelless: exit: too many arguments\n");
		return ;
	}
	exit(ret);
}
