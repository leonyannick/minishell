/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:04:54 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/19 10:56:17 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include <stdbool.h>
# include "../libft/includes/libft.h"

t_list	*parse(t_list *token_head);
void	print_cmd_list(t_list *cmd_head);
void	print_string_list(t_list *head);
void	print_token_list(t_list *token);

#endif
