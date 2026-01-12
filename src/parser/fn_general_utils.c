/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_general_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:58:40 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/04 14:48:37 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	*perror_null(char *str)
{
	perror(str);
	return (NULL);
}

int	msg_int(char *str, int val)
{
	printf ("%s\n", str);
	return (val);
}

void	free_3(void *a, void *b, void *c)
{
	if (a)
		free (a);
	if (b)
		free (b);
	if (c)
		free (c);
	return ;
}

char	*ft_strdup_mod(const char *s1)
{
	size_t	size;
	char	*s1_dup;

	if (!s1)
	{
		ft_putstr_fd ("@ft_strdup_mod: received empty string\n", 2);
		return (NULL);
	}
	size = (ft_strlen(s1) + 1) * sizeof(char);
	s1_dup = (char *)malloc(size);
	if (s1_dup == NULL)
	{
		perror ("@ft_strdup_mod: malloc error");
		return (NULL);
	}
	ft_strlcpy(s1_dup, s1, size);
	return (s1_dup);
}
