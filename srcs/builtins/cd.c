/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:13:03 by lbaumann          #+#    #+#             */
/*   Updated: 2023/06/20 15:55:03 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

/**
 * free new_path because it has been allocated before
*/
static void	update_paths(char *new_path, t_list *dict)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;
	char	*pwd;

	if (!getcwd(cwd, PATH_MAX))
		perror("cd");
	oldpwd = ft_strdup(cwd); 
	if (chdir(new_path))
		perror("cd");
	if (!getcwd(cwd, PATH_MAX))
		perror("cd");
	pwd = ft_strdup(cwd);
	ft_dict_modify_value(dict, "OLDPWD", oldpwd);
	ft_dict_modify_value(dict, "PWD", pwd);
	new_path = ft_free_set_null(new_path);
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
	char	*temp;
	char	*curpath;

	if (!ft_strncmp(arg, ".", 1) || !ft_strncmp(arg, "..", 2) || !ft_strncmp(arg, "/", 1))
		curpath = ft_strdup(arg);
	else
	{
		pwd = ft_dict_get_value(dict, "PWD");
		temp = ft_strjoin(pwd, "/");
		curpath = ft_strjoin(temp, arg);
		free(temp);
	}
	return (curpath);
}

void	builtin_cd(const char **argv, t_list *dict)
{
	char	*path;

	path = NULL;
	// printf("PWD: %s\n", (char *)ft_dict_get_value(dict, "PWD"));
	// printf("OLDPWD: %s\n", (char *)ft_dict_get_value(dict, "OLDPWD"));
	if (argv[2] != NULL)
		printf("cd: too many arguments\n");
	else if (!argv[1] || !ft_strcmp(argv[1], "~") || !ft_strcmp(argv[1], "--"))
	{
		path = ft_strdup(ft_dict_get_value(dict, "HOME"));
		update_paths(path, dict);
	}
	else if (!ft_strcmp(argv[1], "-"))
	{
		path = ft_strdup(ft_dict_get_value(dict, "OLDPWD"));
		update_paths(path, dict);
		return (builtin_pwd());
	}
	else
	{
		path = process_path(argv[1], dict);
		update_paths(path, dict);
	}
	// printf("PWD after: %s\n", (char *)ft_dict_get_value(dict, "PWD"));
	// printf("OLDPWD after: %s\n", (char *)ft_dict_get_value(dict, "OLDPWD"));
}
