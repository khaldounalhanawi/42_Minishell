/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_builtin_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:01 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/17 15:13:52 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"
#include "libft.h"
#include "parser.h"

int	search_builtin_functions(t_exec_context *ctxt)
{
	int		len;
	char	*name;
	int		return_val;

	return_val = 0;
	name = ctxt->cmd_lst->argv->content;
	len = 1024;
	if (ft_strncmp (name, "echo", len) == 0)
		return_val = builtin_echo (ctxt);
	else if (ft_strncmp (name, "cd", len) == 0)
		return_val = builtin_cd (ctxt);
	else if (ft_strncmp (name, "pwd", len) == 0)
		return_val = builtin_pwd (ctxt);
	else if (ft_strncmp (name, "export", len) == 0)
		return_val = builtin_export (ctxt);
	else if (ft_strncmp (name, "unset", len) == 0)
		return_val = builtin_unset (ctxt);
	else if (ft_strncmp (name, "env", len) == 0)
		return_val = builtin_env (ctxt);
	else if (ft_strncmp (name, "exit", len) == 0)
		return_val = builtin_exit (ctxt);
	return (return_val);
}

int	is_builtin(t_cmd *cmd_lst)
{
	char	*name;

	if (!cmd_lst || !cmd_lst->argv)
		return (0);
	name = cmd_lst->argv->content;
	if (ft_strncmp (name, "echo", 5) == 0
		|| ft_strncmp (name, "cd", 3) == 0
		|| ft_strncmp (name, "pwd", 4) == 0
		|| ft_strncmp (name, "export", 7) == 0
		|| ft_strncmp (name, "unset", 6) == 0
		|| ft_strncmp (name, "env", 4) == 0
		|| ft_strncmp (name, "exit", 5) == 0)
	{
		return (1);
	}
	return (0);
}
