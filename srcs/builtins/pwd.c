/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:02:47 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/16 15:00:33 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

void	builtin_pwd(void)
{
	char	*pwd;
	char	cwd[CWD_MAX_SIZE];
	ft_memset(cwd, 0, CWD_MAX_SIZE);
	getcwd(cwd, CWD_MAX_SIZE);
	printf("%s\n", cwd);
}
