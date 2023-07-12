/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:24:32 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/12 12:25:30 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../../libft/includes/libft.h"
# include "../../includes/types.h"
# include "../../includes/builtins.h"
# include "../../includes/data.h"
# include "../../includes/signals.h"

char	**ft_lst_strarr(t_list *list);
int		io_redirection(int in_pipe[2], int out_pipe[2], t_command *command);
void	execute_path_cmd(t_data *data, t_command *command);
void	close_pipe(int pipe[2]);
void	init_pipes(int *in_pipe, int *out_pipe);
void	set_pipes(t_command *command, int *in_pipe, int *out_pipe);
int		read_heredocs(t_list *cmd_head);
void	command_del(void *arg);
int		execute_builtin_cmd(t_data *data, t_command *command);
bool	is_minishell_called(t_data *data, t_command *cmd);

#endif