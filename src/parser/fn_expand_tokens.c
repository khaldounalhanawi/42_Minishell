/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_expand_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:58:40 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/17 18:39:54 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	expand_this_var(char *var, t_exec_context *exec_context,
		char **expanded_var)
{
	char	*temp;

	if (var[0] == '$' && var[1] == '?')
	{
		temp = ft_itoa (exec_context->exit_state);
		if (!temp)
		{
			perror ("@expand_this_var.ft_itoa:");
			return (-1);
		}
		*expanded_var = temp;
	}
	else
	{
		*expanded_var = search_env (&(var[1]), exec_context->envp);
		if (!*expanded_var)
			return (-1);
	}
	return (1);
}

static int	extract_var(char **str, t_exec_context *exec_context,
		int var_len, int i)
{
	char	*var;
	char	*expanded_var;
	char	temp;
	int		len;

	var = &(*str)[i];
	temp = var[var_len];
	var[var_len] = '\0';
	if (expand_this_var (var, exec_context, &expanded_var) == -1)
		return (-1);
	var[var_len] = temp;
	if (replace_var (str, i, var_len, expanded_var) == -1)
	{
		free (expanded_var);
		return (-1);
	}
	len = ft_strlen (expanded_var);
	free (expanded_var);
	return (len);
}

static int	process_str(char **str, t_exec_context *exec_context)
{
	int		i;
	int		var_len;
	int		new_len;

	i = 0;
	while ((*str)[i])
	{
		while ((*str)[i] && (*str)[i] != '$')
			i ++;
		if (!(*str)[i])
			break ;
		var_len = cal_var_len (*str, i);
		if (var_len == 1)
			new_len = 1;
		else
			new_len = extract_var (str, exec_context, var_len, i);
		if (new_len == -1)
			return (-1);
		else
			i += new_len;
	}
	return (1);
}

int	expand_vars(char **str, t_exec_context *exec_context)
{
	int	return_value;

	if (!str || !exec_context->envp)
	{
		ft_putstr_fd ("@expanded_vars: empty input\n", 2);
		return (-1);
	}
	if (!(*str))
		return (0);
	return_value = process_str (str, exec_context);
	return (return_value);
}

int	expand_tokens(t_token *token_lst, t_exec_context *exec_context)
{
	t_token	*token;

	if (!token_lst || !token_lst->content)
		return (-1);
	token = token_lst;
	while (token)
	{
		if (token->type == RINPUT && token->next)
			token = token->next;
		else if (token->type == WORD || token->type == D_QT)
			if (expand_vars(&token->content, exec_context) == -1)
				return (-1);
		token = token->next;
	}
	return (1);
}
