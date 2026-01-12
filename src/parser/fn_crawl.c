/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_crawl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:36:45 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/07 10:11:33 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>

static int	handle_quotes(char **buf, char **p, int pos, t_token_type *type)
{
	char	c;

	c = **p;
	if (c == '\'')
		*type = S_QT;
	else
		*type = D_QT;
	(*p)++;
	while (**p && **p != c)
		(*buf)[pos++] = *(*p)++;
	if (**p != c)
	{
		printf ("@handle_quotes: Unclosed quote sign\n");
		return (-1);
	}
	(*buf)[pos] = '\0';
	(*p)++;
	return (pos);
}

static int	handle_redirects(char *buf, char **p, t_token **head)
{
	t_token	*current;
	char	*str;

	str = *p;
	buf[0] = str[0];
	buf[1] = str[1];
	buf[2] = '\0';
	(*p) += 2;
	current = tls_create (buf);
	if (!current)
		return (-1);
	if (buf[0] == '>')
		current->type = ROUTPUT;
	else if (buf[0] == '<')
		current->type = RINPUT;
	return (tls_add_back (head, current));
}

static int	handle_special(char *buf, char **p, t_token **head)
{
	t_token	*current;
	char	*str;

	str = *p;
	if ((str[0] == '<' && str[1] == '<')
		|| (str[0] == '>' && str[1] == '>'))
		return (handle_redirects (buf, p, head));
	else
	{
		buf[0] = *str;
		buf[1] = '\0';
		(*p)++;
		current = tls_create (buf);
		if (!current)
			return (-1);
		figure_type (&current, buf[0]);
		return (tls_add_back (head, current));
	}
}

static int	handle_word(char *buf, char **str, t_token **head)
{
	int				i;
	t_token_type	type;

	i = 0;
	type = WORD;
	while (!fn_is_space (**str) && !fn_is_res (**str) && **str)
	{
		if (**str == '"' || **str == '\'')
		{
			i = handle_quotes (&buf, str, i, &type);
			if (i == -1)
				return (-1);
			continue ;
		}
		buf[i] = **str;
		(*str)++;
		i ++;
	}
	buf[i] = '\0';
	return (add_buf_to_list (buf, head, type));
}

int	crawl(char *buf, char *str, t_token **head)
{
	while (*str)
	{
		while (fn_is_space (*str))
			str ++;
		if (!*str)
			break ;
		if (fn_is_res (*str))
		{
			if (handle_special (buf, &str, head) == -1)
				return (-1);
		}
		else
		{
			if (handle_word(buf, &str, head) == -1)
				return (-1);
		}
	}
	return (1);
}
