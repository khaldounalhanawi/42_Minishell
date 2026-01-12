/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_unset_II.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/24 17:32:57 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "libft.h"
#include "local_execute.h"

int	get_len_array(char **array)
{
	int	i;

	if (!array || !*array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_str_n_array(char **arr, int pos)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < pos)
	{
		free (arr[i]);
		i++;
	}
	free (arr);
}

int	copy_exclude_str_arr(int index, char ***envp,
	char ***new_envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (i != index)
		{
			(*new_envp)[j] = ft_strdup((*envp)[i]);
			if (!(*new_envp)[j])
			{
				free_str_n_array ((*new_envp), j);
				return (perror_int ("@unset_this.malloc: ", -1));
			}
			j ++;
		}
		i ++;
	}
	(*new_envp)[j] = NULL;
	return (1);
}

int	unset_this(int index, char ***envp)
{
	int		len_envp;
	char	**new_envp;

	len_envp = get_len_array (*envp);
	new_envp = malloc (sizeof (char *) * len_envp);
	if (!new_envp)
		return (perror_int ("@unset_this.malloc: ", -1));
	if (copy_exclude_str_arr (index, envp, &new_envp) == -1)
		return (-1);
	free_str_n_array (*envp, len_envp);
	*envp = new_envp;
	return (1);
}
