#include "parser.h"

void	delete_node(t_treenode *node)
{
	if (node == NULL || (node->type == NULL && node->data == NULL))
		return ;
	if (node->data != NULL)
    {
        free(node->data);
        node->data = NULL;
    }
	if (node->type != NULL)
    {
        free(node->type);
        node->type = NULL;
    }
	delete_node(node->left);
	delete_node(node->right);
}

void	set_node_data_type(t_treenode *node, char *data, t_nodetype nodetype)
{
	if (node == NULL)
		return ;
	if (data != NULL)
		node->data = ft_strdup(data);
	node->type = nodetype;
}

void	attach_tree_branch(t_treenode *root, t_treenode *leftNode, t_treenode
		*rightNode)
{
	if (root == NULL)
		return ;
	root->left = leftNode;
	root->right = rightNode;
}
