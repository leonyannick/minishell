/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:04:54 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/07 14:28:18 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "temp_lexer.h"
# include <stdbool.h>
# include "../libft/includes/libft.h"

typedef enum cmd_type
{
	BUILTIN,
	PATH,
}	e_cmd_type;

typedef struct command
{
	t_list			*arguments;
	e_cmd_type		type;
	bool			has_in_pipe;
	bool			has_out_pipe;
	e_token_types	in_redir_type;
	e_token_types	out_redir_type;
	char			*input_redir_path;
	t_list			*output_redir_path;
}					t_command;

t_list	*parse(t_list *token_head);

#endif
