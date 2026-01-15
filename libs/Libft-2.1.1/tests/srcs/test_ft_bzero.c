/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_bzero.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:11:47 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/05/13 23:44:01 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

int	test_ft_bzero(void)
{
	void	*s;
	void	*s_ft;
	size_t	i;
	size_t	size;

	size = 1000 * sizeof(char);
	s_ft = malloc(size);
	s = malloc(size);
	if (!(s_ft && s))
	{
		printf("Test_ft_bzero: memory allocation for testing failed.\n");
		return (0);
	}
	ft_bzero(s_ft, size);
	bzero(s, size);
	i = 0;
	while (i < size / sizeof(char))
	{
		if(((char *)s_ft)[i] == ((char *)s)[i])
			i++;
		else
			return (0);
	}
	free(s_ft);
	free(s);
	return (1);
}
