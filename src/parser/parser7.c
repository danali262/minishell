#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*redirection_create_root(t_treenode *root, t_treenode *right_node,
				char *filename, int opt)
{
	t_treenode	*filenameNode;

	filenameNode = malloc(sizeof(*filenameNode));
	if (!filenameNode)
		parser_error(filenameNode);
	if (opt == 1)
	{
		set_node_data_type(root, "<", NODE_REDIRECT_IN);
		set_node_data_type(filenameNode, filename, NODE_FILE);
		attach_tree_branch(root, filenameNode, right_node);
	}
	else if (opt == 2)
	{
		set_node_data_type(root, ">", NODE_REDIRECT_OUT);
		set_node_data_type(filenameNode, filename, NODE_FILE);
		attach_tree_branch(root, filenameNode, right_node);
	}
	else
	{
		set_node_data_type(root, ">>", NODE_APPEND);
		set_node_data_type(filenameNode,filename, NODE_FILE);
		attach_tree_branch(root, filenameNode, right_node);
	}
	return (root);
}

void	handle_node_arg(t_treenode *root, t_treenode *tokenlist, char *arg)
{
	arg = strip_quotes(arg, root);
	set_node_data_type(root, arg, NODE_ARG);
	attach_tree_branch(root, tokenlist, NULL);
}

void	handle_node_var(t_treenode *root, t_treenode *tokenlist, char *arg)
{
	arg = strip_quotes(arg, root);
	set_node_data_type(root, arg, NODE_VAR);
	attach_tree_branch(root, tokenlist, NULL);
}

void	handle_both_nodes(t_treenode *root, char *arg)
{
	t_treenode	*argNode;
	char		*var_arg;

	arg = strip_quotes(arg, root);
	set_node_data_type(root, "$?", NODE_VAR);
	argNode = malloc(sizeof(*argNode));
	if (!argNode)
		parser_error(argNode);
	var_arg = create_arg(arg, argNode);
	set_node_data_type(argNode, var_arg, NODE_ARG);
	attach_tree_branch(root, argNode, NULL);
}
