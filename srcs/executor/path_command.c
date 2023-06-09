/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:58:09 by aehrlich          #+#    #+#             */
/*   Updated: 2023/07/13 12:39:21 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

/* 
	frees a string array and sets its pointer to NULL
	to make it unreachable.
	@argument:	pointer to the array of strings, to make it NULL settable
	@return:	none
 */
static char	**free_str_arr(char **strs)
{
	int	i;

	i = 0;
	if (!strs || !*strs)
		return (NULL);
	while (strs[i])
	{
		strs[i] = ft_free_set_null(strs[i]);
		i++;
	}
	ft_free_set_null(strs);
	return (NULL);
}

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
static bool	is_dir(char *path)
{
	struct stat		file_stat;
	
	if (stat((const char *)path, &file_stat))
		return (false);
	if (S_ISDIR(file_stat.st_mode))
	{
		ft_fd_printf(STDERR_FILENO, "ushelless: %s: Is a directory\n", path);
		return (true);
	}
	return (false);
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
	start = free_str_arr(start);
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

	path = (char *)command->arguments->content;
	if (is_dir(path))
		exit_child(data, 126);
	if (!access(path, X_OK))
		joined_path = ft_strdup((char *)command->arguments->content);
	else
		joined_path = build_path(command, data);
	if (!joined_path)
	{
		ft_fd_printf(STDERR_FILENO, "%s: command not found\n",
			(char *)command->arguments->content);
		exit_child(data, EXIT_FAILURE);
	}
	arg_list = ft_lst_strarr(command->arguments);
	envp = ft_dict_to_strarr(data->env_dict);
	if (!envp)
		exit_child(data, EXIT_FAILURE);
	execve(joined_path, arg_list, envp);
	arg_list = free_str_arr(arg_list);
	exit_child(data, EXIT_FAILURE);
}
