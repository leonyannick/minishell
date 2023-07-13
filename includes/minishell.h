/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:42:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/10 17:01:58 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "lexer.h"
# include "types.h"
# include "parser.h"
# include "executor.h"
# include "signals.h"
# include "data.h"
# include <stdlib.h>//malloc
# include <stdio.h>//printf, readline#include <readline/readline.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>//true, false
# include <signal.h>

# define EXIT_CODE_SIGINT 130

#endif