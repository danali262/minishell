#include "parser.h"

t_treenode	*create_node(t_treenode *root, char *operator)
{
	if (ft_strcmp(operator, ">") == 0)
		set_node_data_type(root, operator, NODE_REDIRECT_OUT);
	else if (ft_strcmp(operator, "<") == 0)
		set_node_data_type(root, operator, NODE_REDIRECT_IN);
	else if (ft_strcmp(operator, ">>") == 0)
		set_node_data_type(root, operator, NODE_APPEND);
	else
		set_node_data_type(root, operator, NODE_RHOMBUS);
	return (root);
}

t_treenode	*handle_root_redirection(t_treenode *root, t_treenode
	*node, char *operator, char *filename)
{
	if (ft_strcmp(operator, "<") == 0)
		root = simple_redirection_create_root(root, node, filename, 1);
	else if (ft_strcmp(operator, ">") == 0)
		root = simple_redirection_create_root(root, node, filename, 2);
	else if (ft_strcmp(operator, ">>") == 0)
		root = simple_redirection_create_root(root, node, filename, 3);
	else
		root = simple_redirection_create_root(root, node, filename, 4);
	return (root);
}

t_treenode	*handle_root_redirection_multiple(t_treenode *root, t_treenode
	*node, char *operator, char *filename)
{
	if (ft_strcmp(operator, "<") == 0)
		root = multiple_redirection_create_root(root, node, filename, 1);
	else if (ft_strcmp(operator, ">") == 0)
		root = multiple_redirection_create_root(root, node, filename, 2);
	else if (ft_strcmp(operator, ">>") == 0)
		root = multiple_redirection_create_root(root, node, filename, 3);
	else
		root = multiple_redirection_create_root(root, node, filename, 4);
	return (root);
}

t_treenode	*multiple_redirection_create_root(t_treenode *root, t_treenode
	*right_node, char *filename, int opt)
{
	t_treenode	*filenameNode;

	filenameNode = ft_calloc(1, sizeof(*filenameNode));
	if (!filenameNode)
		parser_error(filenameNode);
	if (opt == 1)
		root = handle_redirect_in_multiple(root, filenameNode, right_node,
				filename);
	else if (opt == 2)
		root = handle_redirect_out_multiple(root, filenameNode, right_node,
				filename);
	else if (opt == 3)
		root = handle_append_multiple(root, filenameNode, right_node, filename);
	else
		root = handle_rhombus_multiple(root, filenameNode, right_node,
				filename);
	return (root);
}

t_treenode	*simple_redirection_create_root(t_treenode *root,
	t_treenode *simplecmdNode, char *filename, int opt)
{
	t_treenode	*filenameNode;

	filenameNode = ft_calloc(1, sizeof(*filenameNode));
	if (!filenameNode)
		parser_error(filenameNode);
	if (opt == 1)
		root = handle_redirect_in_single(root, simplecmdNode, filenameNode,
				filename);
	else if (opt == 2)
		root = handle_redirect_out_single(root, simplecmdNode, filenameNode,
				filename);
	else if (opt == 3)
		root = handle_append_single(root, simplecmdNode, filenameNode,
				filename);
	else
		root = handle_rhombus_single(root, simplecmdNode, filenameNode,
				filename);
	return (root);
}
