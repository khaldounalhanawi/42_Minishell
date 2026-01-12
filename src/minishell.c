/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:54:30 by plima             #+#    #+#             */
/*   Updated: 2025/11/27 20:28:20 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "signals.h"
#include "parser.h"
#include "execute.h"
#include "envp.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

static int	read_parse_and_execute(t_exec_context *exec_context)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		return (1);
	}
	if (*line)
	{
		add_history(line);
		if (parse(line, exec_context) == 1)
		{
			if (exec_context->cmd_lst)
				execute(exec_context);
		}
	}
	free(line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec_context	exec_context;

	register_signals();
	(void)argc;
	(void)argv;
	exec_context.envp = copy_envp(envp);
	if (!exec_context.envp)
		return (-1);
	exec_context.exports = NULL;
	exec_context.exit_state = 0;
	exec_context.cmd_lst = NULL;
	exec_context.token_lst = NULL;
	exec_context.main_pid = getpid();
	while (1)
	{
		if (read_parse_and_execute(&exec_context))
			break ;
	}
	rl_clear_history();
	free_envp(exec_context.envp);
	free_envp(exec_context.exports);
	return (0);
}
