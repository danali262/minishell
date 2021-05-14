#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*cmd(t_curtok *curtok)
{
	t_treenode	*node;
	t_token		*save;

	save = curtok->current_token;
	curtok->current_token = save;
	if ((node = cmd1(curtok)) != NULL)
		return (node);
	curtok->current_token = save;
	if ((node = cmd2(curtok)) != NULL)
		return (node);
	// curtok->current_token = save;
	// if ((node = cmd3(curtok)) != NULL)
	// 	return (node);
	curtok->current_token = save;
	if ((node = cmd4(curtok)) != NULL)
		return (node);
	return (NULL);
}

t_treenode	*cmd1(t_curtok *curtok)		/* <simple command> '<' <filename> */
{
	t_treenode	*simplecmdNode;
	t_treenode	*root;
	t_treenode	*filenameNode;
	char		*filename;

	simplecmdNode = simplecmd(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_LESSER, NULL, curtok))
	{
		delete_node(simplecmdNode);
		return (NULL);
	}
	if (!term(TOKEN, &filename, curtok))
	{
		free(filename);
		delete_node(simplecmdNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	filenameNode = malloc(sizeof(*filenameNode));
	set_node_type(root, NODE_REDIRECT_IN);
	set_node_type(filenameNode, NODE_FILE);
	set_node_data(root, "<");
	set_node_data(filenameNode, filename);
	attach_tree_branch(root, simplecmdNode, filenameNode);
	return (root);
}

t_treenode	*cmd2(t_curtok *curtok)		/* <simple command> '>' <filename> */
{
	t_treenode	*simplecmdNode;
	t_treenode	*root;
	t_treenode	*filenameNode;
	char		*filename;

	simplecmdNode = simplecmd(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_GREATER, NULL, curtok))
	{
		delete_node(simplecmdNode);
		return (NULL);
	}
	if (!term(TOKEN, &filename, curtok))
	{
		free(filename);
		delete_node(simplecmdNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	filenameNode = malloc(sizeof(*filenameNode));
	set_node_type(root, NODE_REDIRECT_OUT);
	set_node_type(filenameNode, NODE_FILE);
	set_node_data(root, ">");
	set_node_data(filenameNode, filename);
	attach_tree_branch(root, simplecmdNode, filenameNode);
	return (root);
}

// t_treenode	*cmd3(t_curtok *curtok)		/* WIP <simple command> '>>' <filename> WIP */
// {
// 	t_treenode	*simplecmdNode;
// 	t_treenode	*filenameNode;
// 	t_treenode	*result;
// 	char		*filename;

// 	simplecmdNode = simplecmd(curtok);
// 	if (simplecmdNode == NULL)
// 		return (NULL);
// 	if (!term(CHAR_GREATER, NULL, curtok->current_token))
// 	{
// 		delete_node(simplecmdNode);
// 		return (NULL);
// 	}
// 	if (!term(TOKEN, &filename, curtok->current_token))
// 	{
// 		free(filename);
// 		delete_node(simplecmdNode);
// 		return (NULL);
// 	}
// 	result = malloc(sizeof(t_treenode));
// 	filenameNode = malloc(sizeof(t_treenode));
// 	set_node_type(result, NODE_REDIRECT_OUT);
// 	set_node_type(filenameNode, NODE_FILE);
// 	set_node_data(filenameNode, filename);
// 	attach_tree_branch(result, filenameNode, simplecmdNode);
// 	return (result);
// }

t_treenode	*cmd4(t_curtok *curtok)
{
	return(simplecmd(curtok));
}