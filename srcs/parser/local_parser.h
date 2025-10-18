/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:41:33 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/17 15:48:13 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_PARSER_H
# define LOCAL_PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "parser.h" // maybe delte?

// fn_tocken_lists.c
int		tls_add_back(t_token **lst, t_token *new);
void	tls_delete_list(t_token **head);
t_token	*tls_create(char *str);
int		add_buf_to_list(char *buf, t_token **head, t_token_type type);

// fn_helpers.c
int		fn_is_space(char c);
int		fn_is_res(char c);
void	figure_type(t_token **current, char c);

// fn_crawl.c
int		crawl(char *buf, char *str, t_token **head);

// fn_expand_vars_utils.c
int		msg_int(char *str, int val);
void	free_3(void *a, void *b, void *c);
char	*ft_strdup_mod(const char *s1);
char	*search_env(char *str, char **envp);
int		replace_var(char **str, int i, int var_len, char *expanded_var);
void	*perror_null(char *str);
#endif