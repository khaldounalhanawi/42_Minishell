/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:01 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/24 12:13:47 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <parser.h>
#include "local_builtin.h"
#include "local_execute.h"
#include "libft.h"

int	builtin_pwd(t_exec_context *ctxt)
{
	char	*text;

	(void)ctxt;
	text = getcwd(NULL, 0);
	if (!text)
	{
		perror ("@pwd:");
		return (-1);
	}
	printf ("%s\n", text);
	free (text);
	return (1);
}
