/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_check_token_sequence.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:17:15 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/07 10:08:07 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "local_parser.h"
#include <unistd.h>

static int	check_pipe(t_token *cur_token, t_token *token_lst);
static int	is_redirection(t_token_type type);
static int	check_redirection(t_token *token);
static int	can_next_cmd_exist(t_token *cur_token);

int	check_token_sequence(t_token *token_lst)
{
	t_token	*cur_token;

	if (!token_lst)
		return (-1);
	cur_token = token_lst;
	while (cur_token)
	{
		if (cur_token->type == PIPE)
		{
			if (check_pipe(cur_token, token_lst) == 0)
				return (0);
		}
		else if (is_redirection(cur_token->type))
		{
			if (check_redirection(cur_token) == 0)
				return (0);
		}
		cur_token = cur_token->next;
	}
	return (1);
}

static int	check_pipe(t_token *cur_token, t_token *token_lst)
{
	if ((cur_token == token_lst) && (cur_token->type == PIPE))
	{
		ft_putstr_fd("minishell: syntax error near token '|'\n", 2);
		return (0);
	}
	if ((cur_token->type == PIPE) && (cur_token->next))
	{
		if (cur_token->next->type == PIPE)
		{
			ft_putstr_fd("minishel: syntax error near token '|'\n", 2);
			return (0);
		}
	}
	if ((cur_token->type == PIPE) && (!cur_token->next))
	{
		ft_putstr_fd("minishel: syntax error near token '|'\n", 2);
		return (0);
	}
	if (can_next_cmd_exist(cur_token) == 0)
	{
		ft_putstr_fd("minishel: syntax error near token '|'\n", 2);
		return (0);
	}
	return (1);
}

static int	is_redirection(t_token_type type)
{
	if (type == INPUT || type == OUTPUT || type == RINPUT || type == ROUTPUT)
		return (1);
	return (0);
}

static int	check_redirection(t_token *token)
{
	if (!token->next)
	{
		ft_putstr_fd("minishel: syntax error near token '", 2);
		ft_putstr_fd(token->content, 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	if ((token->next->type == WORD) || (token->next->type == S_QT)
		|| (token->next->type == D_QT))
		return (1);
	ft_putstr_fd("minishel: syntax error near token '", 2);
	ft_putstr_fd(token->content, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

static int	can_next_cmd_exist(t_token *cur_token)
{
	t_token	*next;

	next = cur_token->next;
	while (next)
	{
		if ((next->type == INPUT) || (next->type == OUTPUT)
			|| (next->type == ROUTPUT) || (next->type == RINPUT))
		{
			if (!next->next)
				return (0);
			next = next->next;
		}
		else if (next->type == WORD || next->type == S_QT || next->type == D_QT)
			return (1);
		else if (next->type == PIPE)
			break ;
		next = next->next;
	}
	return (0);
}
