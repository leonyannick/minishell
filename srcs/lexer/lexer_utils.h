/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:59:02 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/07 11:07:41 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

#include <stdio.h> //printf, readline#include <readline/readline.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h> //true, false
#include "../../libft/includes/libft.h"
#include "../../includes/structs.h"
#include "../../includes/lexer.h"

//lexer_utils_token_1
char	*redirection_token(char *line, size_t *i, e_token_types *type);
char	*parameter_token(char *line, size_t *i, e_token_types *type, char **envp);
char	*quote_token(char *line, size_t *i, e_token_types *type, char **envp);
char	*whitespace_token(char *line, size_t *i, e_token_types *type);
char	*pipe_token(char *line, size_t *i, e_token_types *type);

//lexer_utils_token_2
char	*word_token(char *line, size_t *i, e_token_types *type);
t_token	*assign_token_attr(char *token_str, e_token_types type);
t_list	*save_token(t_list **tokens, char *token_str, e_token_types type);
void	insert_token_before(t_list **tokens, t_list *token_prepended, char *token_str, e_token_types type);

//lexer_utils_helper_1
bool	is_whitespace(char c);
bool	is_quote(char c);
bool	is_metacharacter(char c);
bool	is_operator(char c);
void	skip_whitespace(char *str, size_t *i);

//lexer_utils_helper_2
char	*expand(char *line, size_t *i, char **envp);
char	*char_to_str(char c);
char	*append_str(char *str, char *appendix);

//lexer_utils_postprocess
t_list	*modify_list(t_list **lst, t_list *(*f)(t_list **lst, t_list *node));
t_list	*word_splitting(t_list **tokens, t_list *node);
t_list	*merge_words(t_list **tokens, t_list *node);
t_list	*remove_whitespace(t_list **tokens, t_list *node);
#endif
