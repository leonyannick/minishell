/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:24:32 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/15 18:11:00 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../../libft/includes/libft.h"
# include "../../includes/types.h"

char	**ft_lst_strarr(t_list *list);
int		io_redirection(int in_pipe[2], int out_pipe[2], t_list *command);
int		execute_path_cmd(t_data *data, t_command *command);
int		close_pipe_fd(int **pipes, t_data *data);

#endif