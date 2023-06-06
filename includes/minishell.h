/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:42:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/05/25 17:24:34 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"
#include "temp_lexer.h"
#include "parser.h"
#include <stdlib.h> //malloc
#include <stdio.h> //printf, readline#include <readline/readline.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h> //true, false

//color macro for printing status messages in color
# define GR	"\033[32;1m"
# define RE	"\033[31;1m"
# define PU	"\033[35;1m"
# define BL	"\033[34;1m"
# define YE "\033[33;1m"
# define RC "\033[0m"

#endif
