/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_execute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:54:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/17 15:14:21 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_EXECUTE_H
# define LOCAL_EXECUTE_H

# include "types.h"

// fn_assign_input_output.c
int		assign_input_output(t_cmd *cmd_lst);

// fn_run_cmd.c
int		run_cmd(t_exec_context *exec_context);

// fn_utils.c
void	*free_str_array(char **arr);
int		perror_int(char *str, int val);
int		cmd_lst_count(t_cmd *cmd_lst);

// fn_get_full_path.c
char	*get_full_path(t_cmd *cmd_lst, char **envp);

// fn_create_process_id_arr.c
void	clear_fd_array(int **fd_array, int pos);
int		*create_process_id_arr(int ***fd_array, int count);

// fn_loop_pids.c
int		loop_pids(int *process_id_arr, int **fd_array,
			int count, t_exec_context *exec_context);

// fn_run_builtin_in_parent.c
int		run_builtin_in_parent(t_exec_context *exec_context);

#endif
