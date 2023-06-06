/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:04:54 by aehrlich          #+#    #+#             */
/*   Updated: 2023/05/25 17:44:20 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "temp_lexer.h"
# include "../libft/includes/libft.h"

typedef enum word_type
{
	builtin_cmd,
	path_cmd,
	argument,
	none
}	e_word_type;

typedef struct command
{
	char			*cmd_name;
	t_list			*arguments;
	e_word_type		type;
	e_token_types	in_redir_type;
	e_token_types	out_redir_type;
	char			*input_redir_path;
	char			*output_redir_path;
}					t_command;

#endif
