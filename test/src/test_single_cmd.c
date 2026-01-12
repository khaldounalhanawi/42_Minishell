/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:54:30 by plima             #+#    #+#             */
/*   Updated: 2025/11/04 17:38:17 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	char *str;

	str = NULL;
	str = ft_strdup ("");
	if (!str)
		return (-1);
	expand_vars (&str, envp);
	printf ("%s\n", str);
	free (str);
	argc = 1;
	return (argc);
}
*/

void	print_list(t_token *ls_token)
{
	char *t_str[] = 
	{
	"WORD",
	"PIPE",
	"INPUT",
	"OUTPUT",
	"RINPUT",
	"ROUTPUT",
	"S_QT",
	"D_QT"
	};


	if (ls_token == NULL)
	{
		printf ("list is NULL\n");
		return ;
	}
	while (ls_token->next)
	{
		printf ("%-25s type:%s\n", ls_token->content, t_str[ls_token->type]);

		ls_token = ls_token->next;
	}
	printf ("%-25s type:%s\n", ls_token->content, t_str[ls_token->type]);

}

t_cmd *create_single_ls_cmd(void)
{
    // Allocate the command node
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;

    // Create argv token: "ls"
    t_token *token_ls = malloc(sizeof(t_token));
    if (!token_ls) {
        free(cmd);
        return NULL;
    }
	    // Create argv token 2:
    t_token *token_ls_2 = malloc(sizeof(t_token));
    if (!token_ls_2) {
		free (token_ls);
        free(cmd);
        return NULL;
    }
	    // Create argv token 3:
    t_token *token_ls_3 = malloc(sizeof(t_token));
    if (!token_ls_3) {
		free (token_ls);
		free (token_ls_2);
        free(cmd);
        return NULL;
    }
    // token_ls->content = strdup("user is: $USER | shell is: \"$SHELL\"'plus this' | double user: $USER$USER $ '\"$USER\"' \"'$USER'\" $?");
	// token_ls->content = strdup("multiple: $USER$HOME$SHELL");
	
    token_ls->content = strdup("pwd");
    token_ls->type = D_QT;
    token_ls->next = token_ls_2;
    token_ls_2->content = strdup("-nnn");
    token_ls_2->type = D_QT;
    token_ls_2->next = token_ls_3;
    token_ls_3->content = strdup("falafel");
    token_ls_3->type = D_QT;
    token_ls_3->next = NULL;

    // Fill cmd fields
    cmd->argv = token_ls;       // points to the token list
    cmd->infile = NULL;         // no input file
    cmd->outfile = NULL;
    cmd->append = false;        // '>' not '>>'
    cmd->is_infile_heredoc = false; // heredoc
    cmd->next = NULL;           // single command

    return cmd;
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->content)
			free(token->content);
		free(token);
		token = tmp;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
			free_tokens(cmd->argv);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free(cmd);
		cmd = tmp;
	}
}

void	expand_all (t_cmd *cmd_lst, char **envp)
{
	t_token	*first_token;

	while (cmd_lst)
	{
		expand_vars (&cmd_lst->infile, envp);
		expand_vars (&cmd_lst->outfile, envp);
		first_token = cmd_lst->argv;
		while (cmd_lst->argv)
		{
			expand_vars (&cmd_lst->argv->content, envp);
			cmd_lst->argv = cmd_lst->argv->next;
		}
		cmd_lst->argv = first_token;
		cmd_lst = cmd_lst->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_cmd	*cmd_lst;
	
	cmd_lst = create_single_ls_cmd();

	expand_all (cmd_lst, envp);

	// if (execute (cmd_lst, envp) != 1)
	// {
	// 	free_cmd (cmd_lst);
	// 	return (-1);
	// }
	execute (cmd_lst, envp);
	free_cmd (cmd_lst);
	free (cmd_lst->argv);
	// free (cmd_lst);
	return (0);
}



/*
int	main(void)
{
	char	*line;
	t_token *tokens;

	register_signals();
	while (1)
	{
		line = readline("Minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*line)
		{
			add_history(line);
			tokens = tokenizer(line);
			if (!tokens)
				continue ;
			// tester
			print_list(tokens);
			// tls_delete_list (&ls_token);
		}
	}
	rl_clear_history();
	free(line);
	return (0);
}
*/