/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_check_token_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 21:18:49 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/07 11:00:06 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"
#include "libft.h"
#include <stdio.h>

void		test(char *description, char *input, int expected_out, int *res);
void		print_result(int res, char *description);
static int	is_line_valid(char *line);

int	main(void)
{
	int	res;

	res = 1;
	test("Cmd commes eventually after Pipe", "cat | < infile >outfile cmd", 1, &res);
	test("Cmd does not comme eventually after Pipe", "cat | < infile >outfile", 0, &res);
	test("Cmd does not comme eventually after Pipe + |", "cat | < infile >outfile |", 0, &res);
	test("Pipe followed by WORD, even if not cmd", "cat | a", 1, &res);
	test("Pipe preceeded by S_QT", "cat 'hello world' | echo", 1, &res);
	test("Pipe preceeded by D_QT", "cat \"hello world\" | echo", 1, &res);
	test("Pipe followed by S_QT", "ls | 'echo' $VAR", 1, &res);
	test("Pipe followed by D_QT", "ls | \"echo\" $VAR", 1, &res);
	test("Pipe followed by OUTPUT", "cat | >", 0, &res);
	test("Pipe followed by INPUT", "cat | <", 0, &res);
	test("Pipe followed by ROUTPUT", "cat | >>", 0, &res);
	test("Pipe followed by RINPUT", "cat | <<", 0, &res);
	test("Pipe at the end", "cat |    	", 0, &res);
	test("Pipe preceeded by OUTPUT", "cat > | echo", 0, &res);
	test("Pipe preceeded by INPUT", "cat < | echo", 0, &res);
	test("Pipe preceeded by ROUTPUT", "cat >> | echo", 0, &res);
	test("Pipe preceeded by RINPUT", "cat >> | echo", 0, &res);
	test("Pipe at the beginning", "| echo $VAR", 0, &res);
	test("Pipe followed by |", "cat | echo || echo", 0, &res);
	test("Pipe followed by ||", "ls -l ||| wc -l", 0, &res);
	test("Redirection '>' followed by a WORD ", "ls -l > outfile", 1, &res);
	test("Redirection '>>'followed by a WORD ", "ls -l < outfile", 1, &res);
	test("Redirection '<' followed by a WORD ", "ls -l < outfile", 1, &res);
	test("Redirection '<<'followed by a WORD ", "ls -l < outfile", 1, &res);
	test("Redirection '>' followed by a S_QT ", "ls -l > 'outfile'", 1, &res);
	test("Redirection '>' followed by a D_QT ", "ls -l > \"out\" ", 1, &res);
	test("Redirection '<' followed by a S_QT ", "ls -l < 'out'", 1, &res);
	test("Redirection '<' followed by a D_QT ", "ls -l < \"out\" ", 1, &res);
	test("Redirection '>>' followed by a S_QT ", "ls -l >> 'out'", 1, &res);
	test("Redirection '>>' followed by a D_QT ", "ls -l >> \"out\" ", 1, &res);
	test("Redirection '<<' followed by a S_QT ", "ls -l << 'out'", 1, &res);
	test("Redirection '<<' followed by a D_QT ", "ls -l << \"out\" ", 1, &res);
	test("Redirection '>' at the end", "ls -l >", 0, &res);
	test("Redirection '<' at the end", "ls -l <", 0, &res);
	test("Redirection '>>'at the end", "ls -l >>", 0, &res);
	test("Redirection '<<'at the end", "ls -l <<", 0, &res);
	test("Redirection '>' followed by pipe", "ls -l >    |", 0, &res);
	test("Redirection '<' followed by pipe", "ls -l <  |", 0, &res);
	test("Redirection '>>' followed by pipe", "ls -l >>    |", 0, &res);
	test("Redirection '<<' followed by pipe", "ls -l <<    |", 0, &res);
	if (res == 1)
		printf("\ntest_check_token_sequence: [OK]\n\n");
	else if (res == 0)
		printf("\ntest_check_token_sequence: [NOK]\n\n");
	else if (res == -1)
		printf("\ntest_check_token_sequence: Error\n\n");
	return (0);
}

void	test(char *description, char *input, int expected_out, int *res)
{
	int	ret;

	ret = is_line_valid(input);
	print_result(ret == expected_out, description);
	if (ret != expected_out)
		*res = 0;
	if (ret == -1)
		*res = -1;
}

static int	is_line_valid(char *line)
{
	t_token	*token_lst;

	token_lst = tokenizer(line);
	if (!token_lst)
		return (-1);
	if ((check_token_sequence(token_lst) == 0)
		|| check_token_sequence(token_lst) == -1)
	{
		tls_delete_list (&token_lst);
		return (0);
	}
	tls_delete_list (&token_lst);
	return (1);
}

void	print_result(int res, char *description)
{
	if (res == 1)
		printf("%-50s [OK]\n", description);
	else if (res == 0)
		printf("%-50s [NOK]\n", description);
	else if (res == -1)
		printf("%-50s [Function under test returned error (-1)\n", description);
}
