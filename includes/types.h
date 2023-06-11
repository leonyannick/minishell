/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:33:26 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/11 12:26:20 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "../libft/includes/libft.h"
#include <stdbool.h>

//minishell
typedef struct	data
{
	char	**envp;
	t_list	*tokens;
	t_list	*commands;
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
	WHITESPACE,
	NONE
} e_token_types;

typedef struct s_token
{
	int		type;
	char	*str;
}	t_token;

//parser
typedef enum cmd_type
{
	BUILTIN,
	PATH,
}	t_cmd_type;

typedef struct command
{
	t_list			*arguments;
	t_cmd_type		type;
	bool			has_in_pipe;
	bool			has_out_pipe;
	e_token_types	in_redir_type;
	e_token_types	out_redir_type;
	char			*input_redir_path;
	t_list			*output_redir_path;
}					t_command;

//executor
typedef struct pipeline
{
	int	**pipes;
	int	*pids;
	int	pipe_count;
	
}t_pipeline;

#endif
