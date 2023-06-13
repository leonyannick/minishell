/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:24:32 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/13 11:32:01 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../../libft/includes/libft.h"
# include "../../includes/types.h"

char	**ft_lst_strarr(t_list *list);
int		io_redirection(t_list *command, int **pipes, int index);

#endif