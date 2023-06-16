/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:04:00 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/16 15:07:44 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

static void	print_env_entry(void *arg)
{
	printf("%s=%s\n", ((t_dict *)arg)->key,
		(char *)(((t_dict *)arg)->value));
}

void	builtin_env(t_list *dict)
{
	ft_lstiter(dict, print_env_entry);
}
