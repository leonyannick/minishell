/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:58:09 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/19 12:22:02 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

/* 
	frees a string array and sets its pointer to NULL
	to make it unreachable.
	@argument:	pointer to the array of strings, to make it NULL settable
	@return:	none
 */
static void	free_str_arr(char ***strs)
{
	int	i;

	i = 0;
	if (!*strs)
		return ;
	while ((*strs)[i])
	{
		free((*strs)[i]);
		(*strs)[i] = 0;
		i++;
	}
	free(*strs);
	*strs = 0;
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

	if (access((char *)command->arguments->content, X_OK) == 0)
		joined_path = ft_strdup((char *)command->arguments->content);
	else
	{
		paths = get_paths(data);
		if (!paths)
			return (printf("NO PATHS\n"), -1);
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
	free_str_arr(&start);
	free(joined_path);
	return (-1);
}
