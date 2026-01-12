/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:26:12 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/17 15:10:24 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "parser.h"
#include "libft.h"
#include "local_builtin.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int	change_dir(char *new_wd, char *cur_wd)
{
	if (chdir(new_wd) == -1)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", new_wd);
		free(cur_wd);
		free(new_wd);
		return (-1);
	}
	return (1);
}

static int	get_new_wd(int nr_args, char **new_wd,
						t_exec_context *exec_context)
{
	if (nr_args == 1)
	{
		*new_wd = search_env("HOME", exec_context->envp);
		if (!(*new_wd) || (ft_strncmp(*new_wd, "", 1) == 0))
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (nr_args == 2)
	{
		*new_wd = ft_strdup(exec_context->cmd_lst->argv->next->content);
		if (!(*new_wd))
		{
			ft_putstr_fd("@builtin_cd: new_wd ft_strdup failed\n", 2);
			return (-1);
		}
	}
	else
	{
		ft_printf("bash: cd: too many arguments\n");
		return (1);
	}
	return (0);
}

static int	get_nr_args(t_token *argv)
{
	int	i;

	if (!argv)
	{
		ft_putstr_fd("@fn_builtin_cd: count_args: NULL input\n", 2);
		return (-1);
	}
	i = 1;
	while (argv->next)
	{
		argv = argv->next;
		i++;
	}
	return (i);
}

int	builtin_cd(t_exec_context *exec_context)
{
	char	*cur_wd;
	char	*new_wd;
	int		nr_args;
	int		ret;

	nr_args = get_nr_args(exec_context->cmd_lst->argv);
	if (nr_args == -1)
		return (-1);
	cur_wd = getcwd(NULL, 0);
	ret = get_new_wd(nr_args, &new_wd, exec_context);
	if (ret == -1 || ret == 1)
	{
		free(cur_wd);
		return (ret);
	}
	if (change_dir(new_wd, cur_wd) == -1)
		return (-1);
	free(new_wd);
	if (update_env(cur_wd, exec_context->envp) == -1)
		return (-1);
	free(cur_wd);
	return (1);
}
