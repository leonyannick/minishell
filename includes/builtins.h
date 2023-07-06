/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:06:19 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/06 12:00:50 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	builtin_echo(const char	**argv);
void	builtin_export(const char **argv, t_list *env_dict);
void	builtin_unset(const char **argv, t_list *env_dict);
void	builtin_pwd(void);
void	builtin_env(t_list *env_dict);
void	builtin_cd(const char **argv, t_list *env_dict);
void	builtin_exit(const char **argv);

#endif
