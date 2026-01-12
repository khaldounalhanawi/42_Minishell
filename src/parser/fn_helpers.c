/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:37:52 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/07 10:14:56 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	fn_is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 12))
		return (1);
	else
		return (0);
}

int	fn_is_res(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	else
		return (0);
}

void	figure_type(t_token **current, char c)
{
	if (c == '|')
		(*current)->type = PIPE;
	else if (c == '<')
		(*current)->type = INPUT;
	else if (c == '>')
		(*current)->type = OUTPUT;
	else if (c == '\'')
		(*current)->type = S_QT;
	else if (c == '"')
		(*current)->type = D_QT;
	return ;
}
