/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:02:47 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/28 09:56:21 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

void	builtin_pwd(void)
{
	char	cwd[PATH_MAX];
	
	ft_memset(cwd, 0, PATH_MAX);
	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
}
