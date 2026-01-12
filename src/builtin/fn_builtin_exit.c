/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:13:04 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/30 21:07:06 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "local_builtin.h"
#include "types.h"
#include "envp.h"
#include "parser.h"
#include <stdlib.h>
#include <unistd.h>

static void	cleanup_and_exit(t_exec_context *exec_context, int exit_code)
{
	free_envp(exec_context->envp);
	free_envp(exec_context->exports);
	cmd_lst_delete_list(&exec_context->cmd_lst);
	exit(exit_code);
}

static void	handle_exit_with_two_args(t_exec_context *exec_context)
{
	int		ret;
	long	number;

	ret = ft_strtol(exec_context->cmd_lst->argv->next->content, &number);
	if (ret == -1)
	{
		ft_printf("exit: %s: numeric argument required\n",
			exec_context->cmd_lst->argv->next->content);
		cleanup_and_exit(exec_context, 255);
	}
	if (exec_context->main_pid == getpid())
		ft_printf("exit\n");
	exec_context->exit_state = (unsigned char)number;
	cleanup_and_exit(exec_context, exec_context->exit_state);
}

int	builtin_exit(t_exec_context *exec_context)
{
	int		nr_args;
	t_token	*cur_argv;

	if (!exec_context || !exec_context->cmd_lst
		|| !exec_context->cmd_lst->argv->content)
		cleanup_and_exit(exec_context, EXIT_FAILURE);
	cur_argv = exec_context->cmd_lst->argv;
	nr_args = 1;
	while (cur_argv->next)
	{
		cur_argv = cur_argv->next;
		nr_args++;
	}
	if (nr_args == 1)
	{
		if (exec_context->main_pid == getpid())
			ft_printf("exit\n");
		cleanup_and_exit(exec_context, exec_context->exit_state);
	}
	if (nr_args == 2)
		handle_exit_with_two_args(exec_context);
	ft_printf("exit: too many arguments\n");
	cleanup_and_exit(exec_context, 1);
	return (1);
}
