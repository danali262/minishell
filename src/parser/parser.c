#include "lexer/lexer.h"
#include "parser.h"

static t_treenode	*parser_functions(t_curtok *curtok, t_treenode *syntax_tree)
{
	syntax_tree = command_line(curtok);
	return (syntax_tree);
}

int	parser(t_lexer *lexerbuf, t_treenode *syntax_tree)
{
	t_curtok	curtok;

	if (!lexerbuf->tokens_nbr)
		return (-1);
	curtok.current_token = lexerbuf->tokens_list;
	printf("current token is %s\n", curtok.current_token->data);
	syntax_tree = parser_functions(&curtok, syntax_tree);
	return (0);
}