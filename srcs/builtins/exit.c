/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:39:50 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/21 12:41:20 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

/**
 * return unsigned char 0-255
*/
void	builtin_exit(const char **argv)
{
	unsigned char	ret;
	
	ret = EXIT_SUCCESS;
	if (argv[2] != NULL)
		printf("exit: too many arguments\n");
	if (ft_is_str_nbr(argv[1]))
		ret = (unsigned char)ft_atoi(argv[1]);
	else
		printf("exit: %s: numeric argument required\n", argv[1]);
	exit(ret);
}
