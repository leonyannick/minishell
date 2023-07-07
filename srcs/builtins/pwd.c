/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:02:47 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/07 14:03:42 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

/**
 * pwd also works if you unset the PWD environment variable
 * 
 * set all bytes in cwd to 0, so that cwd is null-terminated after getcwd
 * 
 * PATH_MAX is unsafe:
 * https://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html
 * but regarding the scope of this project I still think it is a good solution
*/
int	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!ft_memset(cwd, 0, PATH_MAX))
		return (error_continue("pwd", NULL, NULL, 0));
	if (!getcwd(cwd, PATH_MAX))
		return (error_continue("pwd", NULL, NULL, 0));
	printf("%s\n", cwd);
	return (EXIT_FAILURE);
}
