/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:30:56 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/13 17:14:51 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <libft.h>
#include <readline/readline.h>

int	g_signal = 0;

void	register_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "\n", 2);
	_exit(130);
}
