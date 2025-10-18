/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:41:33 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/16 15:18:29 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdbool.h>
# include "local_execute.h"

typedef struct s_cmd
{
	t_token			*argv;
	char			*infile;
	char			*outfile;
	bool			append;
	bool			is_infile_heredoc;
	struct s_cmd	*next;
}	t_cmd;

int	execute(t_cmd *cmd_lst, char **envp);

int	cmd_lst_count(t_cmd *cmd_lst);

#endif