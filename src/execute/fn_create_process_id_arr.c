/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_create_process_id_arr.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:55:08 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/12 11:28:41 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

static int	assign_pipes_to_fds(int **fd_array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipe (fd_array[i]) != 0)
		{
			perror ("@assign_pipes_to_fds.pipe: ");
			return (-1);
		}
		i++;
	}
	return (1);
}

void	clear_fd_array(int **fd_array, int pos)
{
	int	i;

	if (!fd_array || !*fd_array)
		return ;
	i = 0;
	while (i < pos)
	{
		free (fd_array[i]);
		i ++;
	}
	free (fd_array);
}

static int	**create_fd_array(int count)
{
	int	**fd_array;
	int	i;

	i = 0;
	fd_array = malloc (sizeof (int *) * (count));
	if (!fd_array)
		return (perror_null("@create_fd_array.fd_array.malloc: "));
	while (i < count)
	{
		fd_array[i] = malloc (sizeof (int) * 2);
		if (!fd_array)
		{
			clear_fd_array (fd_array, i);
			return (perror_null("@create_fd_array.fd_array[i].malloc: "));
		}
		fd_array[i][0] = 0;
		fd_array[i][1] = 0;
		i++;
	}
	return (fd_array);
}

int	*create_process_id_arr(int ***fd_array, int count)
{
	int	*process_id_arr;

	process_id_arr = malloc (sizeof (int) * count);
	if (!process_id_arr)
		return (perror_null ("@create_process_id_arr.malloc:"));
	if (count > 1)
	{
		*fd_array = create_fd_array (count - 1);
		if (!*fd_array)
		{
			free (process_id_arr);
			return (perror_null ("@create_process_id_arr.create_fd_array:"));
		}
		if (assign_pipes_to_fds (*fd_array, count - 1) == -1)
		{
			free (process_id_arr);
			return (NULL);
		}
	}
	else
		*fd_array = NULL;
	return (process_id_arr);
}
