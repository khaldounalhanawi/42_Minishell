/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 04:04:26 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/05/18 22:38:24 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s1_dup;

	size = (ft_strlen(s1) + 1) * sizeof(char);
	s1_dup = (char *)malloc(size);
	if (s1_dup == NULL)
		return (NULL);
	ft_strlcpy(s1_dup, s1, size);
	return (s1_dup);
}
