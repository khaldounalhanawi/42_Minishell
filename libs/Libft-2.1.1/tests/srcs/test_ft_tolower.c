/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_tolower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:01:15 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/05/19 11:52:24 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdio.h>

int test_ft_tolower(void)
{
	int	c;

	c = 0;
	while (c <= 255)
	{
		if (ft_tolower(c) != tolower(c))
			return (0);
		c++;
	}
	if (ft_tolower(EOF) != tolower(EOF))
		return (0);
    return (1);
}