#include "lexer/lexer.h"
#include "parser.h"

int	parser(t_lexer *lexerbuf, t_treenode *syntax_tree)
{
	t_curtok	curtok;
	t_treenode	*child;

	if (!lexerbuf->tokens_nbr)
		return (-1);
	curtok.current_token = lexerbuf->tokens_list;
	// printf("current token is %s\n", curtok.current_token->data);
	syntax_tree = command_line(syntax_tree, &curtok);
	child = malloc(sizeof(t_treenode));
	child = syntax_tree->left;
	if (syntax_tree == NULL)
	{
		printf("syntax tree is NULL\n");
		// print_post_order(syntax_tree);
	}
	else
	{
		printf("SYNTAX TREE DATA is %s\n", syntax_tree->data);
		printf("SYNTAX TREE TYPE is %d\n", syntax_tree->type);
		while (child)
		{
			printf("SYNTAX TREE CHILD is %s\n", child->data);
			child = child->next_sibling;
		}
	}
	return (0);
}