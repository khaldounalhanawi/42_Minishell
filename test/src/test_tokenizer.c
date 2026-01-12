#include "local_parser.h"
#include <stddef.h>
#include <stdio.h>

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

int	main()
{
	t_token	*ls_token;

	// char *str = " ";
	// char *str = "";
	// char *str = "<<<<       ";
	// char *str = "   <'<<'       ";
	// char *str = "<		< <<       ";
	//char *str = "       the \"Weather\"   is | very co<ld but it is not cold>>er 'than this' yester<<day";
	// char *str = "<  >";
	// char *str = "this is a 'tom|ato' but \"falafel is better\" than nothi|ng at all";
	// char *str = "echo 'hi'\"there\"";
	char *str = "echo \"hello 'nested quotes\"";
	// char *str = "echo'a'";
	// char *str = "         kh\"a abc\"kaka\"     samba\"";
	// char *str = "''";
	// char *str = NULL;
	// char *str = "'";

	ls_token = tokenizer(str);
	if (!ls_token)
	{
		printf ("Couldn't create a list of tokens\n");
		return (-1);
	}

	print_list(ls_token);
	tls_delete_list (&ls_token);

}
