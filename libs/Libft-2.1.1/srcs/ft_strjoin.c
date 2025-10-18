/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:42:55 by pecavalc          #+#    #+#             */
/*   Updated: 2025/05/19 00:14:14 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	size;

	size = (ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char);
	dst = (char *)malloc(size);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s1, size);
	ft_strlcat(dst, s2, size);
	return (dst);
}
