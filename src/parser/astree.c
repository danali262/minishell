#include "parser.h"

// t_treenode  *new_node(t_nodetype type)
// {
// 	t_treenode	*node;

// 	node = malloc(sizeof(t_treenode));
// 	if (!node)
// 		return (NULL);
// 	ft_memset(node, 0, sizeof(t_treenode));
// 	node->type = type;
// 	return (node);
// }

// void	free_node_tree(t_treenode *node)
// {
// 	t_treenode	*child;
// 	t_treenode	*next;

// 	if (!node)
// 		return;
// 	child = node->left;
// 	while (child)
// 	{
// 		next = child->next_sibling;
// 		free_node_tree(child);
// 		child = next;	
// 	}
// 	if (node->data)
// 		free(node->data);
// 	free(node);
// }

// void	set_node_val_str(t_treenode *node, char *val)
// {
// 	char	*val2;

// 	val2 = malloc(ft_strlen(val) + 1);
// 	if (!val2)
// 		node->data = NULL;
// 	else
// 	{
// 		ft_strlcpy(val2, val, ft_strlen(val) + 1);
// 		node->data = val2;
// 	}
// }

// void	add_child_node(t_treenode *parent, t_treenode *child)
// {
// 	t_treenode	*sibling;

// 	if (!parent || !child)
// 		return ;
// 	if (!parent->left)
// 		parent->left = child;
// 	else
// 	{
// 		sibling = parent->left;
// 		while(sibling->next_sibling)
// 			sibling = sibling->next_sibling;
// 		sibling->next_sibling = child;
// 		child->prev_sibling = sibling;
// 	}
// 	parent->children++;
// }

void	delete_node(t_treenode *node)
{
	if (node == NULL)
		return ;
	if (node->data)
		free(node->data);
	delete_node(node->left);
	delete_node(node->right);			/* siblings? */
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
		node->data = data;
}

void	attach_tree_branch(t_treenode *root, t_treenode *leftNode, t_treenode *rightNode)
{
	if (root == NULL)
		return ;
	root->left = leftNode;
	root->right = rightNode;
}