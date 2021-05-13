#include "parser.h"

void	add_child_node(t_treenode *parent, t_treenode *child)
{
	t_treenode	*sibling;

	if (!parent || !child)
		return ;
	if (!parent->left)
        parent->left = child;
	else
	{
		sibling = parent->left;
		while(sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children++;
}

void	delete_node(t_treenode *node)
{
	if (node == NULL)
		return ;
	if (node->data)
        free(node->data);
	delete_node(node->left);
	delete_node(node->right);
	free(node);
}

void	set_node_type(t_treenode *node, t_nodetype nodetype)
{
	if (node == NULL)
		return ;			/* should I exit? */
	node->type = nodetype;
}

void	set_node_data(t_treenode *node, char *data)
{
	if (node == NULL)
		return ;
	if (data != NULL)
		node->data = ft_strdup(data);
}

void	attach_tree_branch(t_treenode *root, t_treenode *leftNode, t_treenode *rightNode)
{
	if (root == NULL)
		return ;
	root->left = leftNode;
	root->right = rightNode;
	// root->left->next_sibling = root->right;
}
