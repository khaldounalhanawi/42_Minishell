/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_get_full_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:55:08 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/07 09:59:14 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "local_execute.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int	build_full_path(char **full_path, char *path, char *cmd)
{
	char	*temp;

	temp = ft_strjoin (path, "/");
	if (!temp)
	{
		perror ("@build_full_path.ft_strjoin:");
		return (-1);
	}
	*full_path = ft_strjoin (temp, cmd);
	if (!full_path)
	{
		perror ("@build_full_path.ft_strjoin:");
		free (temp);
		return (-1);
	}
	free (temp);
	return (1);
}

static char	**get_dir_array(char **envp)
{
	char	*line;
	char	**dir_array;

	line = search_env ("PATH", envp);
	if (!line)
		return (NULL);
	dir_array = ft_split (line, ':');
	if (!dir_array)
		return (NULL);
	free (line);
	return (dir_array);
}

char	*get_full_path(t_cmd *cmd_lst, char **envp)
{
	char	**dir_array;
	char	*full_path;
	int		i;

	dir_array = get_dir_array (envp);
	if (!dir_array)
		return (NULL);
	i = 0;
	while (dir_array[i])
	{
		if (build_full_path (&full_path,
				dir_array[i],
				cmd_lst->argv->content) == -1)
			return (free_str_array (dir_array));
		if (access (full_path, X_OK) == 0)
		{
			free_str_array (dir_array);
			return (full_path);
		}
		free (full_path);
		i ++;
	}
	ft_putstr_fd ("couldn't find function path\n", 2);
	return (free_str_array (dir_array));
}
