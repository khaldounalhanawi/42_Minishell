/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:55:08 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/17 21:56:23 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_execute.h"
#include "parser.h"
#include "builtin.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static void	close_all_fds(int **fd_array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close (fd_array[i][0]);
		close (fd_array[i][1]);
		i++;
	}
}

static void	wait_all_pids(int *process_id_arr, int count, int *exit_state)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid (process_id_arr[i], &status, WUNTRACED);
		if (WIFEXITED(status))
			*exit_state = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*exit_state = 128 + WTERMSIG(status);
		if (*exit_state == 131)
			ft_printf("Quit (core dumped)\n");
		i++;
	}
}

static void	cleanup_exec(int **fd_array, int **process_id_arr,
						t_exec_context *exec_context, int count)
{
	clear_fd_array (fd_array, count - 1);
	free (*process_id_arr);
	cmd_lst_delete_list (&exec_context->cmd_lst);
}

static int	execute_body(int *process_id_arr, int **fd_array,
			int count, t_exec_context *exec_context)
{
	t_cmd	*head;

	head = exec_context->cmd_lst;
	process_id_arr = create_process_id_arr (&fd_array, count);
	if (!process_id_arr)
	{
		cmd_lst_delete_list (&head);
		return (-1);
	}
	if (loop_pids (process_id_arr, fd_array, count, exec_context) == -1)
	{
		close_all_fds (fd_array, count - 1);
		exec_context->cmd_lst = head;
		cleanup_exec (fd_array, &process_id_arr, exec_context, count);
		return (-1);
	}
	close_all_fds (fd_array, count - 1);
	wait_all_pids (process_id_arr, count, &(exec_context->exit_state));
	exec_context->cmd_lst = head;
	cleanup_exec (fd_array, &process_id_arr, exec_context, count);
	return (1);
}

int	execute(t_exec_context *exec_context)
{
	int	*process_id_arr;
	int	**fd_array;
	int	count;

	count = cmd_lst_count (exec_context->cmd_lst);
	if (count == 0)
	{
		cmd_lst_delete_list (&exec_context->cmd_lst);
		return (1);
	}
	if (count == 1 && is_builtin(exec_context->cmd_lst))
	{
		if (run_builtin_in_parent(exec_context) == -1)
		{
			cmd_lst_delete_list (&exec_context->cmd_lst);
			return (-1);
		}
		cmd_lst_delete_list (&exec_context->cmd_lst);
		return (1);
	}
	process_id_arr = NULL;
	fd_array = NULL;
	if (execute_body (process_id_arr, fd_array, count, exec_context) == -1)
		return (-1);
	return (1);
}
