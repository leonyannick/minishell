/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:56:18 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/08 11:59:48 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "../includes/temp_lexer.h"
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

unsigned int	ft_cmd_count(t_list *token);
t_command		*ft_create_cmd(void);
t_list			*ft_create_cmd_list(t_list *token_head);
e_cmd_type		ft_get_cmd_type(char *str);
void			print_cmd_list(t_list *cmd_head);
void			print_string_list(t_list *head);
void	print_token_list(t_list *token);

#endif
