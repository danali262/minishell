#include "lexer/lexer.h"
#include "parser.h"

void	print_tree(t_treenode *syntax_tree)
{
	if (!syntax_tree)
		return;
	printf("SYNTAX TREE NODE is %s\n", syntax_tree->data);
	// printf("SYNTAX TREE NODETYPE is %d\n", syntax_tree->type);
	print_tree(syntax_tree->left);
	print_tree(syntax_tree->right);
}

int	parser(t_lexer *lexerbuf, t_treenode *syntax_tree)
{
	t_curtok	curtok;

	if (!lexerbuf->tokens_nbr)
		return (-1);
	curtok.current_token = lexerbuf->tokens_list;
	syntax_tree = command_line(&curtok);
	if (curtok.current_token != NULL && curtok.current_token->type != 0)
	{
		printf("Syntax Error near: %s\n", curtok.current_token->data);
		return (-1);
	}
	if (syntax_tree == NULL)
		printf("syntax tree is NULL\n");
	else
	{
		printf("syntax tree is:\n");
		print_tree(syntax_tree);
	}
	return (0);
}