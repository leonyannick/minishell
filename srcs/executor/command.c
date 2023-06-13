/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:58:09 by aehrlich          #+#    #+#             */
/*   Updated: 2023/06/13 12:33:08 by aehrlich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*ret;
	int		len_s1;
	int		len_s2;

	if (s1 == 0 || s2 == 0)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ret = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (ret == 0)
		return (0);
	ft_strlcpy(ret, s1, len_s1 + 1);
	ft_strlcpy(&ret[len_s1], s2, len_s2 + 1);
	free((void *)s1);
	return (ret);
}

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

int	execute_path_cmd(t_data *data, t_command *command)
{
	char		**paths;
	char		*joined_path;
	char		**start;

	paths = get_paths(data);
	if (!paths)
		return (printf("NO PATHS\n"), -1);
	start = paths;
	while (*paths)
	{
		joined_path = ft_strjoin(*paths, "/");
		joined_path = ft_strjoin_free(joined_path, (char *)command->arguments->content);
		if (access(joined_path, X_OK) == 0)
			break ;
		free(joined_path);
		paths++;
	}
	execve(joined_path, ft_lst_strarr(command->arguments), data->envp);
	perror("execve");
	free_str_arr(&start);
	return (-1);
}