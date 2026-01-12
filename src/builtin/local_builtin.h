/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_builtin.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:54:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/30 21:26:01 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_BUILTIN_H
# define LOCAL_BUILTIN_H

# include "types.h"

int		builtin_echo(t_exec_context *ctxt);
int		builtin_cd(t_exec_context *ctxt);
int		update_env(char *cur_wd, char **envp);
int		builtin_pwd(t_exec_context *ctxt);
int		builtin_export(t_exec_context *ctxt);
int		builtin_unset(t_exec_context *ctxt);
int		builtin_env(t_exec_context *ctxt);
int		builtin_exit(t_exec_context *ctxt);

// fn_built_in_unset_I.c
int		validate_start_letter(char *str);
int		search_key_index(char *str, char **envp);
int		search_index(char *str, char **envp);
int		has_forbidden(char	*str);

// fn_built_in_unset_II.c
int		unset_this(int index, char ***envp);
int		get_len_array(char **array);
void	free_str_n_array(char **arr, int pos);

// fn_quick_sort.c
void	quick_sort(char **str_array, int low, int high);

// fn_built_in_export_II.c
int		update_env_exports(char *content, t_exec_context *ctxt);
int		search_and_unset(char *content, char ***array, char *equal_pos);
// fn_built_in_export_III.c
char	**append_array(char *str, char **array);
bool	is_valid(char *content);

#endif