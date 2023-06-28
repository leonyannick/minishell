/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:58:09 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/28 12:36:06 by aehrlich         ###   ########.fr       */
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
static char	**get_paths()
{
	char	**paths;
	char	*path_string;

	paths = NULL;
	path_string = getenv("PATH");
	if (!path_string)
		return (NULL);
	paths = ft_split(path_string, ':');
	return (paths);
}

static char	*build_path(t_command *command)
{
	char	**paths;
	char	*joined_path;
	char	**start;

	start = NULL;
	paths = get_paths();
	if (!paths)
		return (NULL);
	start = paths;
	while (*paths)
	{
		joined_path = ft_strjoin(*paths, "/");
		joined_path = ft_strjoin_free(
				joined_path,
				(char *)command->arguments->content);
		if (access(joined_path, X_OK) == 0)
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
int	execute_path_cmd(t_data *data, t_command *command)
{
	char	**arg_list;
	char	*joined_path;

	if (access((char *)command->arguments->content, X_OK) == 0)
		joined_path = ft_strdup((char *)command->arguments->content);
	else
		joined_path = build_path(command);
	if (!joined_path)
	{
		ft_fd_printf(STDERR_FILENO, "%s: command not found\n",
			(char *)command->arguments->content);
		return (EXIT_BREAK);
	}
	arg_list = ft_lst_strarr(command->arguments);
	execve(joined_path, arg_list, data->envp);
	arg_list = free_str_arr(arg_list);
	return (EXIT_BREAK);
}
