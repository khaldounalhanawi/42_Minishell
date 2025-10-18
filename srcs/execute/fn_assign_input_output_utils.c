/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_assign_input_output_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:55:08 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/18 11:44:37 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_execute.h"
#include <fcntl.h>

int	check_heredoc_onreturn(t_cmd *cmd_lst, int val)
{
	if (cmd_lst->is_infile_heredoc)
	{
		if (unlink (cmd_lst->infile) != 0)
		{
			perror ("@heredoc_checker.unlink:");
			return (-1);
		}
		else
			return (val);
	}
	return (val);
}
