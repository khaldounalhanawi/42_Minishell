/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_heredoc_prepare.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:57:06 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/15 15:53:49 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "signals.h"
#include <sys/wait.h>

static int	get_exit_code(t_exec_context *exec_context, int status)
{
	if (WIFEXITED(status))
		exec_context->exit_state = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exec_context->exit_state = 128 + WTERMSIG(status);
	if (exec_context->exit_state == 130)
		return (-1);
	return (1);
}

static int	fork_for_heredoc(char *filename, t_token *tok,
			t_exec_context *exec_context)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (-1);
	}
	else if (pid == 0)
		execute_heredoc(filename, tok, exec_context);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, WUNTRACED);
		signal(SIGINT, handle_sigint);
		if (get_exit_code(exec_context, status) == -1)
			return (-1);
	}
	return (1);
}

static char	*get_heredoc_filename(void)
{
	char				*filename;
	char				*tmp;
	static unsigned int	i = 1;

	while (1)
	{
		tmp = ft_itoa(i);
		if (!tmp)
			return (NULL);
		filename = ft_strjoin(".heredoc_tmp_", tmp);
		free(tmp);
		if (!filename)
			return (NULL);
		if (access(filename, F_OK) != 0)
			break ;
		else
		{
			free(filename);
			i++;
		}
	}
	i++;
	return (filename);
}

int	handle_heredoc(t_token *token, t_cmd *cmd, t_exec_context *exec_context)
{
	if (!token || !token->next || !token->next->content || !exec_context)
		return (-1);
	cmd->is_infile_heredoc = true;
	if (!cmd->infile)
		cmd->infile = get_heredoc_filename();
	if (!cmd->infile)
		return (-1);
	if (fork_for_heredoc(cmd->infile, token->next, exec_context) == -1)
		return (-1);
	return (1);
}
