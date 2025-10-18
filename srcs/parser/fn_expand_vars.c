/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:58:40 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/17 09:59:23 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"

static int	cal_var_len(char *str, int i)
{
	int		var_len;

	if (str[i + 1] && str[i] == '$' && str[i + 1] == '?')
	{
		var_len = 2;
		return (var_len);
	}
	var_len = 1;
	while (str[i + var_len]
		&& !fn_is_space (str[i + var_len])
		&& str[i + var_len] != '"'
		&& str[i + var_len] != '\''
		&& str[i + var_len] != '$')
		var_len ++;
	return (var_len);
}

static int expand_this_var(char *var, char **envp, char **expanded_var)
{
	if (var[0] == '$' && var[1] == '?')
	{
		*expanded_var = (ft_strdup_mod ("signal thing"));
		if (!*expanded_var)
		{
			perror ("@expand_this_var.ft_strdup:");
			return (-1);
		}
	}
	else
	{
		*expanded_var = search_env (&(var[1]), envp);
		if (!*expanded_var)
			return (-1);
	}
	return (1);
}

static int	extract_var(char **str, char **envp, int var_len, int i)
{
	char	*var;
	char	*expanded_var;
	char	temp;

	var = &(*str)[i];
	temp = var[var_len];
	var[var_len] = '\0';
	if (expand_this_var (var, envp, &expanded_var) == -1)
		return (-1);
	var[var_len] = temp;
	if (replace_var (str, i, var_len, expanded_var) == -1)
	{
		free (expanded_var);
		return (-1);
	}
	free (expanded_var);
	return (ft_strlen (expanded_var));
}

static int process_str(char **str, char **envp)
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
			new_len = extract_var (str, envp, var_len, i);
		if (new_len == -1)
			return (-1);
		else
			i += new_len;
	}
	return (1);
}

int	expand_vars(char **str, char **envp)
{
	int	return_value;

	if (!str || !envp)
	{
		ft_putstr_fd ("@expanded_vars: empty input", 2);
		return (-1);
	}
	if (!(*str))
		return (0);
	return_value = process_str (str, envp);
	return (return_value);
}
