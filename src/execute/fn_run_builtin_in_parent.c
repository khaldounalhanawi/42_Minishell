/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_run_builtin_in_parent.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:52:57 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/17 13:35:11 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "types.h"
#include "local_execute.h"
#include "builtin.h"

static void	restore_fds(int stdin, int stdout)
{
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
}

int	run_builtin_in_parent(t_exec_context *exec_context)
{
	int	stdin;
	int	stdout;

	if (!*exec_context->cmd_lst->argv->content)
		return (0);
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (stdin == -1 || stdout == -1)
	{
		perror("@run_builtin_in_parent.dup");
		return (-1);
	}
	if (assign_input_output(exec_context->cmd_lst) == -1)
	{
		restore_fds(stdin, stdout);
		return (-1);
	}
	exec_context->exit_state = search_builtin_functions(exec_context);
	if (exec_context->exit_state == -1)
	{
		restore_fds(stdin, stdout);
		return (-1);
	}
	restore_fds(stdin, stdout);
	return (1);
}
