/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_unset_I.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/30 21:21:53 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "libft.h"
#include "local_execute.h"
#include "local_builtin.h"

int	validate_start_letter(char *str)
{
	if (*str != '_' && !ft_isalpha (*str))
		return (0);
	return (1);
}

int	has_forbidden(char	*str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum (str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static int	print_error(char *str)
{
	ft_putstr_fd ("unset: '", 2);
	ft_putstr_fd (str, 2);
	ft_putstr_fd ("': not a valid identifier\n", 2);
	return (-1);
}

int	search_key_index(char *str, char **envp)
{
	int		i;
	int		len;
	char	*key;

	i = 0;
	len = ft_strlen (str) + 1;
	key = ft_strjoin (str, "=");
	if (!key)
		perror_int ("@search_index.ft_strjoin:", -1);
	while (envp[i])
	{
		if (ft_strncmp (key, envp[i], len) == 0)
		{
			free (key);
			return (i);
		}
		i++;
	}
	free (key);
	return (-2);
}

int	builtin_unset(t_exec_context *ctxt)
{
	t_token	*current;
	int		index;

	current = ctxt->cmd_lst->argv->next;
	if (!current || !current->content)
		return (0);
	while (current)
	{
		if (validate_start_letter (current->content) == 0
			|| has_forbidden (current->content) == 1)
			return (print_error (current->content));
		index = search_key_index (current->content, ctxt->envp);
		if (index >= 0 && unset_this (index, &(ctxt->envp)) == -1)
			return (-1);
		else
		{
			if (search_and_unset (current->content, &ctxt->exports, NULL) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (1);
}

/*
int	builtin_unset(t_exec_context *ctxt)
{
	t_token	*current;
	int		index;

	current = ctxt->cmd_lst->argv->next;
	if (!current || !current->content)
		return (0);
	while (current)
	{
		if (validate_start_letter (current->content) == 0
			|| has_forbidden (current->content) == 1)
		{
			print_error (current->content);
			return (-1);
		}
		index = search_key_index (current->content, ctxt->envp);
		if (index >= 0)
		{
			if (unset_this (index, &(ctxt->envp)) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (1);
}

*/
