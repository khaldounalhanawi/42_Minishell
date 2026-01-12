/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_assign_input_output.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:55:08 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/13 17:32:22 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "local_execute.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static int	create_in(t_cmd *cmd_lst)
{
	int	fd;

	fd = open (cmd_lst->infile, O_RDONLY);
	if (fd == -1)
	{
		perror ("@create_in.open:");
		return (-1);
	}
	if (dup2 (fd, STDIN_FILENO) == -1)
	{
		perror ("@create_in.dup2:");
		close (fd);
		return (-1);
	}
	close (fd);
	return (1);
}

static int	open_append(t_cmd *cmd_lst, int *fd)
{
	*fd = open (cmd_lst->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		perror ("@open_append.open:");
		return (-1);
	}
	return (1);
}

static int	open_normal(t_cmd *cmd_lst, int *fd)
{
	*fd = open (cmd_lst->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		perror ("@open_normal.open:");
		return (-1);
	}
	return (1);
}

static int	create_out(t_cmd *cmd_lst)
{
	int	fd;

	if (cmd_lst->append && open_append (cmd_lst, &fd) == -1)
		return (-1);
	else if (!cmd_lst->append && open_normal (cmd_lst, &fd) == -1)
		return (-1);
	if (dup2 (fd, STDOUT_FILENO) == -1)
	{
		perror ("@create_out.dup2:");
		close (fd);
		return (-1);
	}
	close (fd);
	return (1);
}

int	assign_input_output(t_cmd *cmd_lst)
{
	if (cmd_lst->infile && create_in (cmd_lst) == -1)
		return (-1);
	if (cmd_lst->outfile && create_out (cmd_lst) == -1)
		return (-1);
	return (1);
}
