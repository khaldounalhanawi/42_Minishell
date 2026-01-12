/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:36:45 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/07 10:18:02 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "local_parser.h"

static int	set_buffer(char **buf, char *str)
{
	int	len;

	len = ft_strlen (str);
	*buf = malloc (sizeof (char) * (len + 1));
	if (!*buf)
	{
		perror ("@tokenizer.set_buffer:");
		return (-1);
	}
	return (1);
}

t_token	*tokenizer(char *str)
{
	t_token	*head;
	char	*buf;

	head = NULL;
	if (!str || !*str)
	{
		printf ("@tokenizer: NULL input\n");
		return (NULL);
	}
	if (set_buffer (&buf, str) == -1)
		return (NULL);
	if (crawl(buf, str, &head) == -1)
	{
		free (buf);
		tls_delete_list (&head);
		return (NULL);
	}
	free (buf);
	return (head);
}
