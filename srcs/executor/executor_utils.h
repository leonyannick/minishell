/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:24:32 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/20 09:05:37 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include "../../libft/includes/libft.h"
# include "../../includes/types.h"

char	**ft_lst_strarr(t_list *list);
int		io_redirection(int in_pipe[2], int out_pipe[2], t_list *command);
int		execute_path_cmd(t_data *data, t_command *command);
void	close_pipe_if_necessary(int pipe[2]);
void	init_pipes(int *in_pipe, int *out_pipe);
void	set_pipes(int *in_pipe, int *out_pipe, t_command *command);
int		read_heredocs(t_list *cmd_head);

#endif