/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_execute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:54:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/18 11:44:48 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_EXECUTE_H
# define LOCAL_EXECUTE_H

# include "minishell.h"
# include "execute.h"
# include "parser.h"

typedef struct s_cmd	t_cmd;

// fn_assign_input_output.c
int		assign_input_output(t_cmd *cmd_lst);

// fn_assign_input_output_utils.c
int		check_heredoc_onreturn(t_cmd *cmd_lst, int val);

// fn_run_cmd.c
int		run_cmd(t_cmd *cmd_lst, char **envp);

// fn_utils.c
void	*free_str_array(char **arr);

// fn_get_full_path.c
char	*get_full_path(t_cmd *cmd_lst, char **envp);

// built in funs
int		search_builtin_functions(t_cmd *cmd_lst, char **envp);
int		builtin_echo(t_cmd *cmd_lst, char **envp);
int		builtin_cd(t_cmd *cmd_lst, char **envp);
int		builtin_pwd(t_cmd *cmd_lst, char **envp);
int		builtin_export(t_cmd *cmd_lst, char **envp);
int		builtin_unset(t_cmd *cmd_lst, char **envp);
int		builtin_env(t_cmd *cmd_lst, char **envp);
int		builtin_exit(t_cmd *cmd_lst, char **envp);

#endif