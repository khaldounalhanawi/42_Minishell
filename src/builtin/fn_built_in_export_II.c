/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_export_II.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:01 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/12/01 11:01:33 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "local_builtin.h"
#include "local_execute.h"
#include "libft.h"

int	search_and_unset(char *content, char ***array, char *equal_pos)
{
	int		index;

	index = -1;
	if (equal_pos)
	{
		content = ft_substr (content, 0, equal_pos - content);
		if (!content)
			return (perror_int ("@search_and_unset:ft_substring: ", -1));
	}
	index = search_index (content, *array);
	if (index >= 0 && unset_this (index, array) == -1)
	{
		if (equal_pos)
		{
			free (content);
			content = NULL;
		}
		return (-1);
	}
	if (equal_pos)
	{
		free (content);
		content = NULL;
	}
	return (1);
}

int	update_env_exports(char *content, t_exec_context *ctxt)
{
	char	*pos;

	pos = ft_strrchr (content, '=');
	if (pos)
	{
		if (search_and_unset (content, &ctxt->exports, pos) == -1)
			return (-1);
		if (search_and_unset (content, &ctxt->envp, pos) == -1)
			return (-1);
		ctxt->envp = append_array (content, ctxt->envp);
		if (!ctxt->envp)
			return (-1);
	}
	else
	{
		if (search_key_index (content, ctxt->envp) >= 0
			|| search_index (content, ctxt->exports) >= 0)
			return (1);
		ctxt->exports = append_array (content, ctxt->exports);
		if (!ctxt->exports)
			return (-1);
	}
	return (1);
}
