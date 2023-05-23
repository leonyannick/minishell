/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:42:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/05/23 18:21:57 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdio.h> //printf, readline#include <readline/readline.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h> //true, false
#include "../libft/includes/libft.h"

//color macro for printing status messages in color
# define GR	"\033[32;1m"
# define RE	"\033[31;1m"
# define PU	"\033[35;1m"
# define BL	"\033[34;1m"
# define YE "\033[33;1m"
# define RC "\033[0m"

typedef struct s_token	t_token;

typedef enum tokenTypes
{
	I_RED,
	O_RED,
	O_RED_APP,
	I_RED_HD,
	EQUALS,
	PIPE,
	WORD,
	DQUOTES,
	SQUOTES,
	PARAMETER,
} e_tokenTypes;

typedef struct s_token
{
	int		tokenType;
	char	*tokenStr;
}	t_token;

t_list	*getTokens(char *line);

//lexer utils
bool	is_whitespace(char c);
bool	is_metacharacter(char c);

void	test(char *test);

#endif
