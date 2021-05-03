#include "lexer/lexer.h"
#include "parser.h"

static t_treenode	*parser_functions(t_curtok *curtok, t_treenode *syntax_tree)
{
	syntax_tree = command_line(curtok);
	return (syntax_tree);
}



// static t_treenode	*parser_functions(t_token *current_token, t_treenode *syntax_tree)
// {
// 	syntax_tree = parse_simple_command(current_token);
// 	printf("syntax tree is %s\n", syntax_tree->data);
// 	// printf("syntax tree child is %s\n", syntax_tree->left->data);
// 	// printf("syntax tree child's child is %s\n", syntax_tree->left->next_sibling->data);
// 	syntax_tree = syntax_tree->left;
// 	while (syntax_tree != NULL)
// 	{
// 		printf("syntax tree child is %s\n", syntax_tree->data);
// 		// printf("syntax tree child's child is %s\n", syntax_tree->left->data);
// 		syntax_tree = syntax_tree->next_sibling;
// 		// printf("syntax tree child is %s\n", syntax_tree->data);
// 	}
// }

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