/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:21:03 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/03 15:57:00 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>

static int	validate_first_chars(const char *str, int *sign, int *i,
				unsigned long *limit);

int	ft_strtol(const char *str, long *number)
{
	int				i;
	int				sign;
	int				digit;
	unsigned long	result;
	unsigned long	limit;

	i = 0;
	sign = 1;
	result = 0;
	if (validate_first_chars(str, &sign, &i, &limit) == -1)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i++] - '0';
		if (result > (limit - digit) / 10)
			return (-1);
		result = result * 10 + digit;
	}
	if (str[i] != '\0')
		return (-1);
	*number = (long)result * sign;
	return (1);
}

static int	validate_first_chars(const char *str, int *sign, int *i,
		unsigned long *limit)
{
	if (str == NULL || *str == '\0')
		return (-1);
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (*sign == 1)
		*limit = LONG_MAX;
	else
		*limit = -(unsigned long)LONG_MIN;
	if (str[*i] < '0' || str[*i] > '9')
		return (-1);
	return (1);
}
