/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:41:33 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/23 17:16:07 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>

typedef enum e_type
{
	UNSET = -1,
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	RINPUT,
	ROUTPUT,
	S_QT,
	D_QT
}	t_token_type;

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	t_token_type	type;
}	t_token;

typedef struct s_cmd
{
	t_token			*argv;
	char			*infile;
	bool			is_infile_heredoc;
	char			*outfile;
	bool			append;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec_context
{
	t_token	*token_lst;
	t_cmd	*cmd_lst;
	char	**envp;
	char	**exports;
	int		exit_state;
	int		main_pid;
}			t_exec_context;

#endif