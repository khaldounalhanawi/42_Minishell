/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:58:43 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/24 17:23:53 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	switch_elements(char **str1, char **str2)
{
	char	*temp;

	temp = *str2;
	*str2 = *str1;
	*str1 = temp;
}

static int	partition(char **str_array, int low, int high)
{
	int		i;
	int		j;
	char	*pivot;

	i = low - 1;
	j = low;
	pivot = str_array[high];
	while (j < high)
	{
		if (ft_strcmp (str_array[j], pivot) < 0)
		{
			i++;
			switch_elements (&str_array[i], &str_array[j]);
		}
		j++;
	}
	switch_elements (&str_array[i + 1], &str_array[high]);
	return (i + 1);
}

void	quick_sort(char **str_array, int low, int high)
{
	int		position;

	if (low < high)
	{
		position = partition (str_array, low, high);
		quick_sort (str_array, low, position - 1);
		quick_sort (str_array, position + 1, high);
	}
}
/*
int main()
{
	char	**str_array;
	int		i;

	str_array = malloc (sizeof (char *) * 5 + 1);
	str_array[0] = "abc";
	str_array[1] = "a";
	str_array[2] = "";
	str_array[3] = "ABC";
	str_array[4] = "KHALDOUN";
	str_array[5] = NULL;

	quick_sort (str_array, 0 , 4);

	i = 0;
	while (i < 5)
	{
		printf ("%s\n", str_array[i]);
		i ++;
	}
	free (str_array);
	return (0);
}
*/
