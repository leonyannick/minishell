/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:03:12 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/07 15:38:10 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMP_LEXER_H
# define TEMP_LEXER_H

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
	WHITESPACE,
	NONE
} e_token_types;

typedef struct s_token
{
	int		token_type;
	char	*token_str;
}	t_token;

#endif