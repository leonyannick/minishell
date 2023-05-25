/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:33:09 by lbaumann          #+#    #+#             */
/*   Updated: 2023/05/25 15:41:56 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

#include <stdio.h> //printf, readline#include <readline/readline.h>
#include <stdbool.h> //true, false
#include <stdlib.h>
#include <errno.h>
#include "../libft/includes/libft.h"

void	error_fatal(char *error_msg, void *mem);
void	error_soft(char *error_msg, void *mem);

#endif

