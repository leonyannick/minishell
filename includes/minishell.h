/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:42:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/07 16:07:30 by lbaumann         ###   ########.fr       */
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
# include <stdlib.h>//malloc
# include <stdio.h>//printf, readline#include <readline/readline.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>//true, false
# include <signal.h>

//color macro for printing status messages in color
# define GR	"\033[32;1m"
# define RE	"\033[31;1m"
# define PU	"\033[35;1m"
# define BL	"\033[34;1m"
# define YE "\033[33;1m"
# define RC "\033[0m"

void	init_data(t_data *data, char **envp);

#endif