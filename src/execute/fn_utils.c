/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:55:08 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/24 11:08:02 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "types.h"

void	*free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		free (arr[i]);
		i++;
	}
	free (arr);
	return (NULL);
}

int	perror_int(char *str, int val)
{
	perror (str);
	return (val);
}

int	cmd_lst_count(t_cmd *cmd_lst)
{
	int	len;

	if (!cmd_lst)
		return (0);
	len = 1;
	while (cmd_lst->next)
	{
		len ++;
		cmd_lst = cmd_lst->next;
	}
	return (len);
}
