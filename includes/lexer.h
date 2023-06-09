/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:42:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/09 12:16:46 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "types.h"

t_list	*scan_tokens(char *line, t_data *data);
void	token_del(void *arg);
void	print_token(void *arg);
void	print_e_token_types(e_token_types type);

#endif