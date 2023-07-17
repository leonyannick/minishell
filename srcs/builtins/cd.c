/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:13:03 by lbaumann          #+#    #+#             */
/*   Updated: 2023/07/17 16:59:47 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

/**
 * switch to new_path and update OLDPWD and PWD
 * order of operations:
 * 1) save cwd in oldpwd
 * 2) change dir to new_path
 * 3) save new cwd (now new_path) in pwd
 * 4) update OLDPWD and PWD in env_dict
 * get_cwd avoids the hassle of reformatting new_path
 * free new_path because it has been allocated before
*/
static int	update_paths(char *new_path, const char *arg, t_list *env_dict)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;
	char	*pwd;

	if (!getcwd(cwd, PATH_MAX))
		return (error_continue("cd", NULL, NULL, 0));
	oldpwd = ft_strdup(cwd); 
	if (chdir(new_path))
		return (error_continue("cd", arg, "No such file or directory",
			EXIT_FAILURE));
	if (!getcwd(cwd, PATH_MAX))
		return (error_continue("cd", NULL, NULL, 0));
	pwd = ft_strdup(cwd);
	ft_dict_modify_value(env_dict, "OLDPWD", oldpwd);
	ft_dict_modify_value(env_dict, "PWD", pwd);
	if (!ft_dict_get_value(env_dict, "OLDPWD"))
		free(oldpwd);
	if (!ft_dict_get_value(env_dict, "PWD"))
		free(pwd);
	new_path = ft_free_set_null(new_path);
	return (0);
}

/**
 * cd [directory]
 * 
 * [directory] starts with:
 * . or .. -> set curpath to the [directory] operand
 * '/' -> absolute path: curpath = [directory]
 * no slash -> relative path: strjoin PWD and [directory]
*/
static char	*process_path(const char *arg, t_list *env_dict)
{
	char	*pwd;
	char	*temp;
	char	*curpath;

	if (arg[0] == '~' && arg[1] == 0)
		return (ft_strdup(getenv("HOME")));
	if (!ft_strncmp(arg, ".", 1) || !ft_strncmp(arg, "..", 2)
		|| !ft_strncmp(arg, "/", 1))
		curpath = ft_strdup(arg);
	else
	{
		pwd = ft_dict_get_value(env_dict, "PWD");
		temp = ft_strjoin(pwd, "/");
		curpath = ft_strjoin(temp, arg);
		free(temp);
	}
	return (curpath);
}

/**
 * change directories
 * 
 * if there is more than one argument return EXIT_FAILURE
 * 
 * '-': switch to last directory (directory saved in OLDPWD)
 * no arg | '~' | "--": go to home (directory saved in HOME)
 * all other cases: try to go to directory stated as arg
 * return with EXIT_SUCCESS in all these cases
*/
int	builtin_cd(const char **argv, t_list *env_dict)
{
	char	*path;
	int		argc;
	int		ret;

	argc = ft_argc_from_argv(argv);
	if (argc > 2)
		return (error_continue("cd", NULL, "too many arguments", EXIT_FAILURE));
	if (argc != 1 && !ft_strcmp(argv[1], "-"))
	{
		path = ft_strdup(ft_dict_get_value(env_dict, "OLDPWD"));
		if (!path)
			return (error_continue("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
	}
	else if (argc == 1 || !ft_strcmp(argv[1], "--"))
	{
		path = ft_strdup(ft_dict_get_value(env_dict, "HOME"));
		if (!path)
			return (error_continue("cd", NULL, "HOME not set", EXIT_FAILURE));
	}
	else
		path = process_path(argv[1], env_dict);
	ret = update_paths(path, argv[1], env_dict);
	if (argc != 1 && !ft_strcmp(argv[1], "-") && !ret)
		builtin_pwd();
	return (ret);
}
