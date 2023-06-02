/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:42:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/02 10:22:37 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h> //printf, readline#include <readline/readline.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h> //true, false
#include "../libft/includes/libft.h"
#include "../includes/error.h"

#include "../includes/lexer.h"

//color macro for printing status messages in color
# define GR	"\033[32;1m"
# define RE	"\033[31;1m"
# define PU	"\033[35;1m"
# define BL	"\033[34;1m"
# define YE "\033[33;1m"
# define RC "\033[0m"

typedef struct	data
{
	char	**envp;
	t_list	*tokens;
}	t_data;

void	init_data(t_data *data, char **envp);
void	print_token(void *arg);

#endif

