#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*handle_redirect_in_multiple(t_treenode *root, t_treenode *left_node,
	t_treenode *right_node, char *filename)
{
	set_node_data_type(root, "<", NODE_REDIRECT_IN);
	set_node_data_type(left_node, filename, NODE_FILE);
	attach_tree_branch(root, left_node, right_node);
	return (root);
}

t_treenode	*handle_redirect_out_multiple(t_treenode *root, t_treenode
	*left_node, t_treenode *right_node, char *filename)
{
	set_node_data_type(root, ">", NODE_REDIRECT_OUT);
	set_node_data_type(left_node, filename, NODE_FILE);
	attach_tree_branch(root, left_node, right_node);
	return (root);
}

t_treenode	*handle_append_multiple(t_treenode *root, t_treenode *left_node,
	t_treenode *right_node, char *filename)
{
	set_node_data_type(root, ">>", NODE_APPEND);
	set_node_data_type(left_node, filename, NODE_FILE);
	attach_tree_branch(root, left_node, right_node);
	return (root);
}

t_treenode	*handle_rhombus_multiple(t_treenode *root, t_treenode *left_node,
	t_treenode *right_node, char *filename)
{
	set_node_data_type(root, "<>", NODE_RHOMBUS);
	set_node_data_type(left_node, filename, NODE_FILE);
	attach_tree_branch(root, left_node, right_node);
	return (root);
}
