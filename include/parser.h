/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:41:33 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/17 15:50:05 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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

t_token	*tokenizer(char *str);
int		fn_is_space(char c);
int		expand_vars(char **str, char **envp);
int		msg_int(char *str, int val);
void	free_3(void *a, void *b, void *c);
char	*ft_strdup_mod(const char *s1);
void	*perror_null(char *str);
char	*search_env(char *str, char **envp);

#endif