/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_add_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:57:06 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/09 18:33:14 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static int	init_argv(t_cmd *cur_cmd, t_token *cur_token);

int	add_argv(t_token *cur_token, t_cmd *cur_cmd)
{
	t_token	*new_argv_node;

	if (!cur_token || !cur_cmd)
		return (-1);
	if (!cur_cmd->argv)
	{
		if (init_argv(cur_cmd, cur_token) == -1)
			return (-1);
		return (1);
	}
	new_argv_node = tls_create(cur_token->content);
	if (!new_argv_node)
		return (-1);
	if (tls_add_back(&cur_cmd->argv, new_argv_node) == -1)
	{
		free(new_argv_node);
		return (-1);
	}
	new_argv_node->type = cur_token->type;
	return (1);
}

static int	init_argv(t_cmd *cur_cmd, t_token *cur_token)
{
	if (!cur_cmd || !cur_token)
	{
		ft_putstr_fd("@init_argv: NULL input\n", 2);
		return (-1);
	}
	if (!cur_token->content || (cur_token->content[0] == '\0'))
	{
		ft_putstr_fd("@init_argv: \"\" cmd not found\n", 2);
		return (-1);
	}
	cur_cmd->argv = tls_create(cur_token->content);
	if (!cur_cmd->argv)
		return (-1);
	cur_cmd->argv->type = cur_token->type;
	return (1);
}
