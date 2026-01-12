/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_loop_pids.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:55:08 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/30 21:06:36 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_execute.h"
#include "signals.h"
#include "envp.h"
#include "parser.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void	cleanup_after_child(int **fd_array, int count, int *process_id_arr,
								t_exec_context *exec_context)
{
	clear_fd_array(fd_array, count - 1);
	free(process_id_arr);
	cmd_lst_delete_list(&exec_context->cmd_lst);
}

static int	connect_pipes(int **fd_array, int pos, int count)
{
	if (!fd_array || !*fd_array)
		return (0);
	if (pos > 0)
	{
		if (dup2 (fd_array[pos - 1][0], STDIN_FILENO) == -1)
			return (perror_int ("@connect_pipes.dup2: ", -1));
	}
	if (pos + 1 <= count)
	{
		if (dup2 (fd_array[pos][1], STDOUT_FILENO) == -1)
			return (perror_int ("@connect_pipes.dup2: ", -1));
	}
	pos = 0;
	while (pos < count)
	{
		close (fd_array[pos][0]);
		close (fd_array[pos][1]);
		pos++;
	}
	return (1);
}

static int	run_on_child(int **fd_array, t_exec_context *exec_context,
						int i, int count)
{
	int	ret;

	signal(SIGQUIT, SIG_DFL);
	if (connect_pipes(fd_array, i, count - 1) == -1)
	{
		free_envp(exec_context->envp);
		free_envp(exec_context->exports);
		return (-1);
	}
	if (assign_input_output (exec_context->cmd_lst) == -1)
	{
		free_envp(exec_context->envp);
		free_envp(exec_context->exports);
		return (-1);
	}
	ret = run_cmd(exec_context);
	free_envp(exec_context->envp);
	free_envp(exec_context->exports);
	return (ret);
}

int	loop_pids(int *process_id_arr, int **fd_array,
			int count, t_exec_context *exec_context)
{
	int		i;
	int		ret;
	t_cmd	*head;

	head = exec_context->cmd_lst;
	i = 0;
	while (i < count)
	{
		process_id_arr[i] = fork();
		if (process_id_arr[i] == -1)
			return (perror ("@loop_pids.fork"), -1);
		if (process_id_arr[i] == 0)
		{
			ret = run_on_child(fd_array, exec_context, i, count);
			exec_context->cmd_lst = head;
			cleanup_after_child(fd_array, count, process_id_arr, exec_context);
			exit(ret);
		}
		if (exec_context->cmd_lst->next)
			exec_context->cmd_lst = exec_context->cmd_lst->next;
		i++;
	}
	return (1);
}
