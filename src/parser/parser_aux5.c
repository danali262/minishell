#include "lexer/lexer.h"
#include "parser.h"

void	handle_node_arg(t_treenode *root, t_treenode *tokenlist, char *arg)
{
	set_node_data_type(root, arg, NODE_ARG);
	attach_tree_branch(root, tokenlist, NULL);
}

void	handle_node_var(t_treenode *root, t_treenode *tokenlist, char *arg)
{
	set_node_data_type(root, arg, NODE_VAR);
	attach_tree_branch(root, tokenlist, NULL);
}

void	handle_both_nodes(t_treenode *root, char *arg)
{
	t_treenode	*argNode;
	char		*var_arg;

	set_node_data_type(root, "$?", NODE_VAR);
	argNode = malloc(sizeof(*argNode));
	if (!argNode)
		parser_error(argNode);
	var_arg = create_arg(arg, argNode);
	set_node_data_type(argNode, var_arg, NODE_ARG);
	attach_tree_branch(root, argNode, NULL);
}
