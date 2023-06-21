/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:58:09 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/21 17:05:16 by aehrlich         ###   ########.fr       */
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
		free(strs[i]);
		strs[i] = 0;
		i++;
	}
	free(strs);
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
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split((data->envp[i] + ft_strlen("PATH")), ':');
			break ;
		}
		i++;
	}
	return (paths);
}

/* 
	Searchs for a vaild execution path with the envp.
	If successful executes the command in its child process.
	@argument - data:		data object containing the envp for the PATHS
	@argument - command:	command to execute
 */
int	execute_path_cmd(t_data *data, t_command *command)
{
	char		**paths;
	char		*joined_path;
	char		**start;

	joined_path = NULL;
	start = NULL;
	if (access((char *)command->arguments->content, X_OK) == 0)
		joined_path = ft_strdup((char *)command->arguments->content);
	else
	{
		paths = get_paths(data);
		if (!paths)
			return (-1);
		start = paths;
		while (*paths)
		{
			joined_path = ft_strjoin(*paths, "/");
			joined_path = ft_strjoin_free(
					joined_path,
					(char *)command->arguments->content);
			if (access(joined_path, X_OK) == 0)
				break ;
			free(joined_path);
			paths++;
		}
	}
	execve(joined_path, ft_lst_strarr(command->arguments), data->envp);
	perror("execve");
	joined_path = ft_free_set_null((void *)joined_path);
	start = free_str_arr(start);
	return (-1);
}

int	exeute_builtin_cmd(t_data *data, t_command *command, int exit_type)
{
	if (!data)
		return (-1);
	printf("BUILTIN\n");
	return (exit_type);
}
