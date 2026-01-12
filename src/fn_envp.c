/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:54:30 by plima             #+#    #+#             */
/*   Updated: 2025/11/30 21:05:49 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	free_envp(char **envp)
{
	size_t	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		i++;
	while (i > 0)
		free(envp[--i]);
	free(envp);
	envp = NULL;
}

static int	copy_env_line(char **envp, char **new_envp, size_t i)
{
	new_envp[i] = ft_strdup(envp[i]);
	if (!new_envp[i])
	{
		free_envp(new_envp);
		perror("@copy_environment.ft_strdup");
		return (-1);
	}
	return (1);
}

char	**copy_envp(char **envp)
{
	char	**new_envp;
	size_t	i;
	size_t	length;

	i = 0;
	while (envp[i])
		i++;
	length = i;
	new_envp = (char **)malloc((length + 1) * sizeof(char *));
	if (!new_envp)
	{
		perror("@copy_environment.malloc");
		return (NULL);
	}
	i = 0;
	while (i < length)
	{
		if (copy_env_line(envp, new_envp, i) == -1)
			return (NULL);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
