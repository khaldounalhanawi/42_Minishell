/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_export_I.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:01 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/12/01 09:46:40 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "local_builtin.h"
#include "local_execute.h"
#include "libft.h"

static void	fill_temp(char **temp, char **envp, char **exports)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		temp[i] = envp [i];
		i ++;
	}
	if (!exports || !*exports)
		return ;
	while (exports[j])
	{
		temp[i] = exports[j];
		j ++;
		i ++;
	}
}

static int	print_exports(t_exec_context *ctxt)
{
	char	**temp;
	int		len;
	int		i;

	len = get_len_array (ctxt->envp) + get_len_array (ctxt->exports);
	temp = malloc (sizeof (char *) * (len + 1));
	if (!temp)
		return (perror_int ("@print_exports: ", -1));
	temp [len] = NULL;
	fill_temp (temp, ctxt->envp, ctxt->exports);
	quick_sort (temp, 0, len - 1);
	i = -1;
	while (++i < len)
		printf ("declare -x %s\n", temp[i]);
	free (temp);
	temp = NULL;
	return (1);
}

int	search_index(char *str, char **envp)
{
	int		i;
	int		len;

	if (!envp)
		return (-1);
	i = 0;
	len = ft_strlen (str);
	while (envp[i])
	{
		if (ft_strncmp (str, envp[i], len + 1) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-2);
}

int	builtin_export(t_exec_context *ctxt)
{
	t_token	*current_arg;

	if (!ctxt->cmd_lst->argv->next)
		return (print_exports (ctxt));
	current_arg = ctxt->cmd_lst->argv->next;
	while (current_arg)
	{
		if (!is_valid (current_arg->content))
		{
			printf ("@export: `%s': not a valid identifier\n",
				current_arg->content);
			current_arg = current_arg->next;
			continue ;
		}
		if (update_env_exports (current_arg->content, ctxt) == -1)
			return (-1);
		current_arg = current_arg->next;
	}
	return (1);
}
