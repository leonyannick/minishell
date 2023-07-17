/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:04:00 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/17 09:25:11 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

static void	print_env_entry(void *arg)
{
	if ((((t_dict *)arg)->value))
		printf("%s=%s\n", ((t_dict *)arg)->key,
			(char *)(((t_dict *)arg)->value));
}

/**
 * iterates env_dict and prints out the key-value pairs in the format:
 * <key>=<value>
 * if the value is null nothing is printed (different than export)
*/
int	builtin_env(t_list *env_dict)
{
	ft_lstiter(env_dict, print_env_entry);
	return (EXIT_SUCCESS);
}
