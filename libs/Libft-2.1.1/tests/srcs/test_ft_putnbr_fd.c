/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_putnbr_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:37:04 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/09/07 01:00:27 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"

int	test_ft_putnbr_fd(void)
{
	int		fd;

	fd = open("_test_ft_putnbr_fd_test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Cannot read file.\n");
		return (0);
	}
    ft_putnbr_fd(-42000042, fd);
	close(fd);
	printf("%-30s [File created, inspect visually: _test_ft_putnbr_fd_test.txt]\n", "test_ft_putnbr_fd");
	return (-1);
}
