/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:33:26 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/05 10:35:53 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "../libft/includes/libft.h"

//minishell
typedef struct	data
{
	char	**envp;
	t_list	*tokens;
}	t_data;

//lexer
typedef enum token_types
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
	WHITESPACE
} e_token_types;

typedef struct s_token
{
	int		token_type;
	char	*token_str;
}	t_token;

#endif
