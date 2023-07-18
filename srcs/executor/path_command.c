/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:58:09 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/18 12:05:53 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

/* 
	splits the PATHS data representation of the PATHS environ var
	and creates an array of strings.
	@argument - data:	data object containing the envp
	@return:			arry of strings with the available paths
 */
static char	**get_paths(t_data *data)
{
	char	**paths;
	char	*path_string;

	paths = NULL;
	path_string = ft_dict_get_value(data->env_dict, "PATH");
	if (!path_string)
		return (NULL);
	paths = ft_split(path_string, ':');
	return (paths);
}

/**
 * return true if the path leads to a directory
 * else return false
*/
static bool	is_dir(char *path, bool print_err)
{
	struct stat		file_stat;

	if (stat((const char *)path, &file_stat))
		return (false);
	if (S_ISDIR(file_stat.st_mode))
	{
		if (print_err)
			ft_fd_printf(STDERR_FILENO, "ushelless: %s: Is a directory\n", path);
		return (true);
	}
	return (false);
}

static bool	contains_valid_dir(char *path)
{
	char	*slash;
	char	*candidate;
	bool	ret;

	slash = ft_strchr((const char *)path, '/');
	if (!slash)
		return (false);
	if ((slash - path) == 0)
		return (true);
	candidate = ft_substr(path, 0, slash - path);
	if (is_dir(candidate, false))
		ret = true;
	else
		ret = false;
	free(candidate);
	return (ret);
}

/*
	checks for every accessible path if there exists an
	executable using the environ variable. 
	@return:	on success a joined path with the executable
				on failure NULL
*/
static char	*build_path(t_command *command, t_data *data)
{
	char	**paths;
	char	*joined_path;
	char	**start;

	start = NULL;
	paths = get_paths(data);
	if (!paths)
		return (NULL);
	start = paths;
	while (*paths)
	{
		joined_path = ft_strjoin(*paths, "/");
		joined_path = ft_strjoin_free(
				joined_path,
				(char *)command->arguments->content);
		if (!access(joined_path, X_OK))
			break ;
		joined_path = ft_free_set_null(joined_path);
		paths++;
	}
	start = ft_free_split_arr(start);
	return (joined_path);
}

/* 
	Searchs for a vaild execution path with the envp.
	If successful executes the command in its child process.
	@argument - data:		data object containing the envp for the PATHS
	@argument - command:	command to execute
 */
void	execute_path_cmd(t_data *data, t_command *command)
{
	char	**arg_list;
	char	*joined_path;
	char	**envp;
	char	*path;

	joined_path = NULL;
	path = (char *)command->arguments->content;
	if (is_dir(path, true))
		exit_child(data, 126);
	if (!access(path, X_OK))
		joined_path = ft_strdup(path);
	else if (!contains_valid_dir(path) && ft_strcmp(path, ""))
		joined_path = build_path(command, data);
	if (!ft_dict_get_value(data->env_dict, "PATH")
		|| (contains_valid_dir(path) && access(path, X_OK)))
		exit_child(data, error_continue(path, NULL, NOFILE, 127));
	if (!joined_path)
		exit_child(data, error_continue(NULL, path, NOCMD, 127));
	arg_list = ft_lst_strarr(command->arguments);
	envp = ft_dict_to_strarr(data->env_dict);
	if (!envp)
		exit_child(data, EXIT_FAILURE);
	execve(joined_path, arg_list, envp);
	arg_list = ft_free_split_arr(arg_list);
	exit_child(data, EXIT_FAILURE);
}
