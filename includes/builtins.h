/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:06:19 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/07 16:59:28 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "types.h"

int		builtin_echo(const char	**argv);
int		builtin_export(const char **argv, t_list *env_dict);
int		builtin_unset(const char **argv, t_list *env_dict);
int		builtin_pwd(void);
int		builtin_env(t_list *env_dict);
int		builtin_cd(const char **argv, t_list *env_dict);
void	builtin_exit(const char **argv, t_data *data);

#endif
