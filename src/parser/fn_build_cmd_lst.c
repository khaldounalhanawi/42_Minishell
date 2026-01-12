/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_build_cmd_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:57:06 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/13 14:36:23 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "local_parser.h"
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

static int	handle_out_and_rout(t_token *token, t_cmd *cmd)
{
	int	fd;

	free(cmd->outfile);
	cmd->outfile = ft_strdup(token->next->content);
	if (!cmd->outfile)
		return (-1);
	if (token->type == OUTPUT)
		fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
	{
		fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		cmd->append = true;
	}
	if (fd == -1)
	{
		ft_putstr_fd("@handle_redirection: could not create file\n", 2);
		return (-1);
	}
	close(fd);
	return (1);
}

static int	handle_redirection(t_token *token, t_cmd *cmd,
		t_exec_context *exec_context)
{
	if (token->type == INPUT)
	{
		free(cmd->infile);
		cmd->infile = ft_strdup(token->next->content);
		if (!cmd->infile)
			return (-1);
	}
	else if (token->type == OUTPUT || token->type == ROUTPUT)
	{
		if (handle_out_and_rout(token, cmd) == -1)
			return (-1);
	}
	else if (token->type == RINPUT)
	{
		if (handle_heredoc(token, cmd, exec_context) == -1)
			return (-1);
	}
	return (1);
}

static int	convert_token(t_token **token, t_cmd **cmd,
		t_exec_context *exec_context)
{
	if (((*token)->type == WORD) || ((*token)->type == S_QT)
		|| ((*token)->type == D_QT))
	{
		if (add_argv(*token, *cmd) == -1)
			return (-1);
	}
	else if ((*token)->type == PIPE)
	{
		*cmd = cmd_lst_create();
		if (!*cmd || (cmd_lst_add_back(&(exec_context->cmd_lst), *cmd) == -1))
			return (-1);
	}
	else if (((*token)->type == INPUT) || ((*token)->type == OUTPUT)
		|| ((*token)->type == RINPUT) || ((*token)->type == ROUTPUT))
	{
		if (handle_redirection(*token, *cmd, exec_context) == -1)
			return (-1);
		*token = (*token)->next;
	}
	return (1);
}

int	build_cmd_lst(t_token *token_lst, t_exec_context *exec_context)
{
	t_cmd	*cmd;
	t_token	*token;

	if (!token_lst)
		return (-1);
	token = token_lst;
	cmd = cmd_lst_create();
	if (!cmd)
		return (-1);
	if (cmd_lst_add_back(&(exec_context->cmd_lst), cmd) == -1)
	{
		free(cmd);
		return (-1);
	}
	while (token)
	{
		if (convert_token(&token, &cmd, exec_context) == -1)
		{
			cmd_lst_delete_list(&(exec_context->cmd_lst));
			return (-1);
		}
		token = token->next;
	}
	return (1);
}
