#include "lexer/lexer.h"
#include "parser.h"

// void	print_tree(t_treenode *syntax_tree)		/* to be deleted */
// {
// 	if (!syntax_tree)
// 		return;
// 	printf("SYNTAX TREE NODE is %s\n", syntax_tree->data);
// 	printf("SYNTAX TREE NODETYPE is %d\n", syntax_tree->type);
// 	print_tree(syntax_tree->left);
// 	print_tree(syntax_tree->right);
// }

static void    count_nodes(t_treenode *syntax_tree, t_shell *shell)
{
    if (!syntax_tree)
        return ;
    if (syntax_tree->type == 0)
        shell->nbr_semis++;
    if (syntax_tree->type == 1)
        shell->nbr_pipes++;
    count_nodes(syntax_tree->left, shell);
    count_nodes(syntax_tree->right, shell);
}

int	parser(t_lexer *lexerbuf, t_shell *shell)
{
	t_curtok	curtok;

	if (!lexerbuf->tokens_nbr)
		return (-1);
	curtok.current_token = lexerbuf->tokens_list;
	shell->syntax_tree = command_line(&curtok);
	if (curtok.current_token != NULL && curtok.current_token->type != 0)
	{
		printf("Syntax Error near: %s\n", curtok.current_token->data);
		return (-1);
	}
	// if (shell->syntax_tree == NULL)		/* to be deleted */
	// 	printf("syntax tree is NULL\n");
	// else
	// {
	// 	printf("syntax tree is:\n");
	// 	print_tree(shell->syntax_tree);
	// }
	count_nodes(shell->syntax_tree, shell);
    // printf("number of semicolons is %d\n", shell->nbr_semis);
    // printf("number of pipes is %d\n", shell->nbr_pipes);
	return (0);
}