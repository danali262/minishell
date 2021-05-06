#include "lexer/lexer.h"
#include "parser.h"

// static void	print_post_order(t_treenode *syntax_tree)
// {

// }


int	parser(t_lexer *lexerbuf, t_treenode *syntax_tree)
{
	t_curtok	curtok;

	if (!lexerbuf->tokens_nbr)
		return (-1);
	curtok.current_token = lexerbuf->tokens_list;
	// printf("current token is %s\n", curtok.current_token->data);
	syntax_tree = command_line(syntax_tree, &curtok);
	if (syntax_tree == NULL)
	{
		printf("syntax tree is NULL\n");
		// print_post_order(syntax_tree);
	}
	else
	{
		printf("SYNTAX TREE DATA is %s\n", syntax_tree->data);
		printf("SYNTAX TREE TYPE is %d\n", syntax_tree->type);
		printf("SYNTAX TREE LEFT CHILD is %s\n", syntax_tree->left->data);
		// printf("SYNTAX TREE RIGHT CHILD is %s\n", syntax_tree->right->data);
	}
	return (0);
}