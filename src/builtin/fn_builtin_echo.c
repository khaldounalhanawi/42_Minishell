/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:01 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/13 18:34:58 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "parser.h"

static bool	is_flag(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 2;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (false);
			i ++;
		}
	}
	else
		return (false);
	return (true);
}

static void	no_newline_check(t_cmd *cmd_lst, bool *no_newline)
{
	while (cmd_lst->argv)
	{
		if (is_flag (cmd_lst->argv->content))
		{
			*no_newline = true;
			cmd_lst->argv = cmd_lst->argv->next;
		}
		else
			return ;
	}
}

static void	print_loop(t_cmd *cmd_lst)
{
	while (cmd_lst->argv)
	{
		printf ("%s", cmd_lst->argv->content);
		if (cmd_lst->argv->next)
			printf (" ");
		cmd_lst->argv = cmd_lst->argv->next;
	}
}

int	builtin_echo(t_exec_context *ctxt)
{
	t_token	*start;
	bool	no_newline;

	no_newline = false;
	start = ctxt->cmd_lst->argv;
	ctxt->cmd_lst->argv = ctxt->cmd_lst->argv->next;
	no_newline_check (ctxt->cmd_lst, &no_newline);
	print_loop (ctxt->cmd_lst);
	if (!no_newline)
		printf ("\n");
	ctxt->cmd_lst->argv = start;
	return (1);
}
