/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:13:03 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/19 15:24:04 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

/**
 * free new_path because it has been allocated before
*/
static void	update_paths(char *new_path, t_list *dict)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		perror("cd");
	ft_dict_modify_value(dict, "OLDPWD", cwd);
	if (!chdir(new_path))
		perror("cd");
	if (!getcwd(cwd, PATH_MAX))
		perror("cd");
	ft_dict_modify_value(dict, "PWD", cwd);
	new_path = ft_free_set_null(new_path);
}

void	error_cd(const char *msg)
{
	printf("%s\n", msg);
}

static char	*skip_fwdslashes(char *path)
{
	while (*path == '/')
		path++;
	return (path);
}

/**
 * cd [directory]
 * 
 * [directory] starts with:
 * . or .. -> set curpath to the [directory] operand
 * '/' -> absolute path: curpath = [directory]
 * no slash -> relative path: strjoin PWD and [directory]
*/
char	*process_path(const char *arg, t_list *dict)
{
	char	*pwd;
	char	*curpath;

	if (!ft_strncmp(arg, ".", 1) || !ft_strncmp(arg, "..", 2) || !ft_strncmp(arg, "/", 1))
		curpath = ft_strdup(arg);
	else
	{
		pwd = ft_dict_get_value(dict, "PWD");
		curpath = ft_strjoin(pwd, arg);
	}
	return (curpath);
}

void	builtin_cd(const char **argv, t_list *dict)
{
	char	*path;

	path = NULL;
	if (argv[2])
		printf("cd: too many arguments\n");
	else if (!argv[1] || !ft_strcmp(argv[1], "~") || !ft_strcmp(argv[1], "--"))
		path = ft_dict_get_node(dict, "HOME");
	else if (!ft_strcmp(argv[1], "-"))
	{
		path = ft_dict_get_node(dict, "OLDPWD");
		update_paths(path, dict);
		return (builtin_pwd());
	}
	else
		path = process_path(argv[1], dict);
	if (path)
		update_paths(path, dict);
}
