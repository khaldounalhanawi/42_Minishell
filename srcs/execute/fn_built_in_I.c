/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_I.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:01 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/18 18:06:55 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_execute.h"

int	search_builtin_functions(t_cmd *cmd_lst, char **envp)
{
	int		len;
	char	*name;
	int		return_val;

	return_val = 0;
	name = cmd_lst->argv[0].content;
	len = ft_strlen (name);
	if (ft_strncmp (name, "echo", len) == 0)
		return_val = builtin_echo (cmd_lst, envp);
	else if (ft_strncmp (name, "cd", len) == 0)
		return_val = builtin_cd (cmd_lst, envp);
	else if (ft_strncmp (name, "pwd", len) == 0)
		return_val = builtin_pwd (cmd_lst, envp);
	else if (ft_strncmp (name, "export", len) == 0)
		return_val = builtin_export (cmd_lst, envp);
	else if (ft_strncmp (name, "unset", len) == 0)
		return_val = builtin_unset (cmd_lst, envp);
	else if (ft_strncmp (name, "env", len) == 0)
		return_val = builtin_env (cmd_lst, envp);
	else if (ft_strncmp (name, "exit", len) == 0)
		return_val = builtin_exit (cmd_lst, envp);
	return (return_val);
}

int	builtin_echo(t_cmd *cmd_lst, char **envp)
{
	t_token	*start;

	(void)envp;
	start = cmd_lst->argv;
	if (cmd_lst->argv->next)
		cmd_lst->argv = cmd_lst->argv->next;
	else
	{
		printf ("nothing to echo\n");
		cmd_lst->argv = start;
		return (1);
	}
	while (cmd_lst->argv)
	{
		printf ("%s", cmd_lst->argv->content);
		if (cmd_lst->argv->next)
			printf (" ");
		cmd_lst->argv = cmd_lst->argv->next;
	}
	printf ("\n");
	cmd_lst->argv = start;
	return (1);
}

int	builtin_cd(t_cmd *cmd_lst, char **envp)
{
	(void)cmd_lst;
	(void)envp;
	printf("builtin_cd called\n");
	return (1);
}

int	builtin_pwd(t_cmd *cmd_lst, char **envp)
{
	(void)cmd_lst;
	(void)envp;
	printf("builtin_pwd called\n");
	return (1);
}

int	builtin_export(t_cmd *cmd_lst, char **envp)
{
	(void)cmd_lst;
	(void)envp;
	printf("builtin_export called\n");
	return (1);
}
