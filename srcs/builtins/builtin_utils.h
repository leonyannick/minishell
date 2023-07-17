/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:56:13 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/17 16:31:01 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_UTILS_H
# define BUILTIN_UTILS_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>//getenv
# include <limits.h>
# include <sys/errno.h>
# include "../../libft/includes/libft.h"
# include "../../includes/error.h"
# include "../../includes/builtins.h"
# include "../../includes/minishell.h"

char	*replace_home(char *old_arg);

extern int	g_exit_code;

#endif
