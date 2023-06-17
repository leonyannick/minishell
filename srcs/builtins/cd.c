/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:13:03 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/16 16:38:40 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

static void	update_paths(char *new_path, t_list *dict)
{
	char	*pwd;

	pwd = ft_dict_get_value(dict, "PWD");
	ft_dict_modify_value(dict, "PWD", new_path);
	ft_dict_modify_value(dict, "OLDPWD", pwd);
}

void	error_cd(const char *msg)
{
	printf("%s\n", msg);
}

static char	*skip_fwdslashes(char *path)
{
	
}

char	*process_path(const char *arg)
{
	char	*curpath;

	curpath = ft_strdup(arg);
	
}

void	builtin_cd(const char **argv, t_list *dict)
{
	char	*path;

	path = NULL;
	if (argv[2])
		printf("cd: too many arguments\n");
	else if (!argv[1] || !ft_strcmp(argv[1], "~"))
		path = ft_dict_get_node(dict, "HOME");
	else if (!ft_strcmp(argv[1], "-"))
		path = ft_dict_get_node(dict, "OLDPWD");
	else
		path = process_path(argv[1]);
	if (path)
	{
		update_paths(path, dict);
		chdir(path);
	}
}
