#include "lexer/lexer.h"
#include "parser.h"

void	print_tree(t_treenode *syntax_tree)		/* to be deleted */
{
	if (!syntax_tree)
		return ;
	printf("SYNTAX TREE NODE is %s\n", syntax_tree->data);
	printf("SYNTAX TREE NODETYPE is %d\n", syntax_tree->type);
	print_tree(syntax_tree->left);
	print_tree(syntax_tree->right);
}

int	parser(t_lexer_state *lex_state, t_shell *shell)
{
	t_curtok	curtok;

	curtok.current_token = lex_state->tokens_list;
	shell->syntax_tree = command_line(&curtok);
	if (curtok.current_token != NULL && curtok.current_token->type != 0)
	{
		ft_putstr_fd("Syntax Error near: ", STDOUT_FILENO);
		ft_putstr_fd(curtok.current_token->data, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		shell->exit_code = 258;
		return (ERROR);
	}
	// if (shell->syntax_tree == NULL) /* to be deleted */
	// 	printf("syntax tree is NULL\n");
	// else
	// {
	// 	printf("syntax tree is:\n");
	// 	print_tree(shell->syntax_tree);
	// }
	return (SUCCESS);
}
