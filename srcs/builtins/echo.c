/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:55:20 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/16 12:29:37 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

/**
 * return true if the string arg starts with a flag '-' and contains only 'n'
 * afterwards
 * only '-' is also returned as false
*/
static bool	check_n_flag(const char *arg)
{
	if (!arg || (*arg++) != '-' || !(*arg))
		return (false);
	while (*arg)
	{
		if (*arg != 'n')
			return (false);
		arg++;
	}
	return (true);
}

/**
 * the most unimportant string checking i have done in my life
 * if the second str in arr contains the n flag no new line is printed in the
 * end
 * preluding -n flag strings are skipped (once a str that is no n flag is
 * reached, further n flags are treated as normal strings and printed out)
*/
void	builtin_echo(const char **argv)
{
	bool	n_flag;
	size_t	i;

	n_flag = check_n_flag(argv[1]);
	if (n_flag)
		i = 2;
	else
		i = 1;
	while (check_n_flag(argv[i]))
		i++;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}

// int	main(void)
// {
// 	char arg1[] = "echo";
// 	char arg2[] = "-nnnnnn";
// 	char arg3[] = "-nnnnnn";
// 	char arg4[] = "test";
// 	char *argv[5];
// 	argv[0] = arg1;
// 	argv[1] = arg2;
// 	argv[2] = arg3;
// 	argv[3] = arg4;
// 	argv[4] = 0;
// 	builtin_echo(argv);
// }
