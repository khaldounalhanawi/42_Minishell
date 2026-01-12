/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_heredoc_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:57:06 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/28 15:03:48 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"
#include "libft.h"
#include "envp.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "signals.h"

static void	cleanup_and_exit(t_exec_context *exec_context,
				int fd, int exit_code)
{
	free_envp(exec_context->envp);
	free_envp(exec_context->exports);
	cmd_lst_delete_list_no_unlink(&(exec_context->cmd_lst));
	tls_delete_list(&exec_context->token_lst);
	close(fd);
	exit(exit_code);
}

static int	check_and_expand_line(char **line, t_token_type type,
		t_exec_context *exec_context)
{
	int	ret;

	if (type == WORD)
	{
		ret = expand_vars(line, exec_context);
		if (ret == 0 || ret == -1)
			return (-1);
	}
	return (1);
}

static int	read_and_write_line(t_token *tok, int fd,
		t_exec_context *exec_context)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		ft_printf("warning: heredoc ended by end-of-file, wanted 'eof'\n");
		return (1);
	}
	if (ft_strncmp(line, tok->content, ft_strlen(tok->content) + 1) == 0)
	{
		free(line);
		return (1);
	}
	if (check_and_expand_line(&line, tok->type, exec_context) == -1)
	{
		free(line);
		return (-1);
	}
	ft_putendl_fd(line, fd);
	free(line);
	return (0);
}

void	execute_heredoc(char *filename, t_token *tok,
		t_exec_context *exec_context)
{
	int	fd;
	int	ret;

	signal(SIGINT, heredoc_handle_sigint);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		exit (EXIT_FAILURE);
	while (1)
	{
		ret = read_and_write_line(tok, fd, exec_context);
		if (ret == -1)
			cleanup_and_exit(exec_context, fd, EXIT_FAILURE);
		if (ret == 1)
			cleanup_and_exit(exec_context, fd, EXIT_SUCCESS);
	}
}
