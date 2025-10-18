/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:58:40 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/17 09:59:23 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "local_parser.h"

char	*search_env(char *str, char **envp)
{
	int		i;
	int		len;
	char	*key;

	i = 0;
	len = ft_strlen (str) + 1;
	key = ft_strjoin (str, "=");
	if (!key)
		return (perror_null ("@search_env.ft_strjoin:"));
	while (envp[i])
	{
		if (ft_strncmp (key, envp[i], len) == 0)
		{
			free (key);
			return (ft_strdup_mod (&envp[i][len]));
		}
		i++;
	}
	free (key);
	return (ft_strdup_mod (""));
}

int	replace_var(char **str, int i, int var_len, char *expanded_var)
{
	char	*before;
	char	*after;
	char	*temp;

	before = ft_substr (*str, 0, i);
	if (!before)
		return (msg_int("@replace_var.before", -1));
	temp = ft_strjoin (before, expanded_var);
	if (!temp)
	{
		free (before);
		return (msg_int("@replace_var.temp", -1));
	}
	after = ft_strjoin (temp, &(*str)[i + var_len]);
	if (!after)
	{
		free_3 (before, temp, NULL);
		return (msg_int("@replace_var.after", -1));
	}
	free_3 (before, temp, *str);
	*str = after;
	return (1);
}