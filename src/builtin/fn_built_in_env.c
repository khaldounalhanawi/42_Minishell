/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 23:59:17 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/16 00:02:31 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"

int	builtin_env(t_exec_context *exec_context)
{
	int	i;

	i = 0;
	while (exec_context->envp[i])
		ft_printf("%s\n", exec_context->envp[i++]);
	return (1);
}
