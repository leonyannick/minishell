/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:56:18 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/09 12:15:12 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "../includes/lexer.h"
# include "../libft/includes/libft.h"

unsigned int	ft_cmd_count(t_list *token);
t_command		*ft_create_cmd(void);
t_list			*ft_create_cmd_list(t_list *token_head);
t_cmd_type		ft_get_cmd_type(char *str);
void			ft_set_pipe(t_list **cmd_head, bool *is_first_word);
void			ft_set_input_redirection(t_list **token_head,
					t_list *cmd_head);
void			ft_set_output_redirection(t_list **token_head,
					t_list *cmd_head);
void			ft_set_words(t_list *token_head,
					t_list *cmd_head,
					bool *is_first_word);
bool			ft_is_redirection(e_token_types type);
#endif
