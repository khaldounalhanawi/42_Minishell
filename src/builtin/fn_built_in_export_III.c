/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_export_III.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:01 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/12/01 10:48:05 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <parser.h>
#include "local_builtin.h"
#include "local_execute.h"
#include "libft.h"

static int	has_forbidden_n(char *str, int len)
{
	int		i;

	i = 0;
	while (str[i] && i < len)
	{
		if (!ft_isalnum (str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

bool	is_valid(char *content)
{
	char	*char_position;

	if (!validate_start_letter (content))
		return (false);
	char_position = ft_strrchr (content, '=');
	if (char_position)
	{
		if (has_forbidden_n (content,
				char_position - content) == 1)
			return (false);
		else
			return (true);
	}
	else
	{
		if (has_forbidden (content) == 1)
			return (false);
	}
	return (true);
}

static int	copy_array_n_content(char **new_array, char **array, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		new_array[i] = ft_strdup (array[i]);
		if (!(new_array[i]))
		{
			free_str_n_array (new_array, i);
			return (perror_int ("@copy_content.malloc:", -1));
		}
	}
	return (i);
}

char	**append_array(char *str, char **array)
{
	int		len;
	int		i;
	char	**new_array;

	if (!array)
		len = 0;
	else
		len = get_len_array (array);
	new_array = malloc (sizeof (char *) * (len + 2));
	if (!new_array)
		return (perror_null ("@append_array.malloc:"));
	i = copy_array_n_content (new_array, array, len);
	if (i == -1)
		return (NULL);
	new_array[i] = ft_strdup (str);
	if (!new_array[i])
		return (perror_null ("@append_array.ft_strdup:"));
	new_array[i + 1] = NULL;
	free_str_array (array);
	return (new_array);
}
