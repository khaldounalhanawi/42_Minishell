/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_run_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:55:08 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/17 22:17:53 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parser.h"
#include "local_execute.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	arg_len(t_cmd *cmd_lst)
{
	int		len;
	t_token	*start;

	len = 0;
	start = cmd_lst->argv;
	while (cmd_lst->argv)
	{
		len ++;
		cmd_lst->argv = cmd_lst->argv->next;
	}
	cmd_lst->argv = start;
	return (len);
}

void	*clear_args_array(char **p, int i)
{
	int	j;

	perror ("@get_args.ft_strdup:");
	if (!p)
		return (NULL);
	j = 0;
	while (j < i)
	{
		free (p[j]);
		j ++;
	}
	free (p);
	return (NULL);
}

char	**get_args(t_cmd *cmd_lst)
{
	char	**p;
	int		len;
	int		i;
	t_token	*record;

	len = arg_len (cmd_lst);
	p = malloc (sizeof (char *) * (len + 1));
	if (!p)
		return (perror_null ("@get_args:"));
	i = 0;
	record = cmd_lst->argv;
	while (i < len)
	{
		p[i] = ft_strdup (cmd_lst->argv->content);
		if (!p[i])
			return (clear_args_array (p, i));
		cmd_lst->argv = cmd_lst->argv->next;
		i ++;
	}
	p[i] = NULL;
	cmd_lst->argv = record;
	return (p);
}

int	run_external(t_cmd *cmd_lst, char **envp)
{
	char	*full_path;
	char	**args;

	if (ft_strchr (cmd_lst->argv->content, '/'))
		full_path = cmd_lst->argv->content;
	else
	{
		full_path = get_full_path (cmd_lst, envp);
		if (!full_path)
			return (127);
	}
	args = get_args (cmd_lst);
	if (!args)
		return (-1);
	if (execve (full_path, args, envp) == -1)
	{
		free_str_array (args);
		free (full_path);
		return (-1);
	}
	return (1);
}

int	run_cmd(t_exec_context *exec_context)
{
	int	builtin;
	int	ret;

	if (!*exec_context->cmd_lst->argv->content)
		return (0);
	builtin = search_builtin_functions (exec_context);
	if (builtin == 1)
	{
		exec_context->exit_state = 1;
		return (1);
	}
	else if (builtin == -1)
	{
		exec_context->exit_state = -1;
		return (-1);
	}
	ret = run_external(exec_context->cmd_lst, exec_context->envp);
	return (ret);
}
