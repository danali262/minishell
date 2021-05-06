#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*cmd(t_treenode *syntax_tree, t_curtok *curtok)
{
	// printf("i am in cmd\n");
	// if ((syntax_tree = cmd1(syntax_tree, curtok)) != NULL)
	// 	return (syntax_tree);
	// if ((syntax_tree = cmd2(syntax_tree, curtok)) != NULL)
	// 	return (syntax_tree);
	// if ((node = cmd3(curtok)) != NULL)
	// 	return (node);
	if ((syntax_tree = cmd4(syntax_tree, curtok)) != NULL)
		return (syntax_tree);
	return (NULL);
}

// t_treenode	*cmd1(t_treenode *syntax_tree, t_curtok *curtok)		/* <simple command> '<' <filename> */
// {
// 	t_treenode	*simplecmdNode;
// 	t_treenode	*filenameNode;
// 	char		*filename;

// 	printf("i am in cmd1\n");
// 	simplecmdNode = simplecmd(syntax_tree, curtok);
// 	if (simplecmdNode == NULL)
// 		return (NULL);
// 	if (!term(CHAR_LESSER, NULL, curtok))
// 	{
// 		delete_node(simplecmdNode);
// 		return (NULL);
// 	}
// 	if (!term(TOKEN, &filename, curtok))
// 	{
// 		free(filename);
// 		delete_node(simplecmdNode);
// 		return (NULL);
// 	}
// 	syntax_tree = malloc(sizeof(t_treenode));
// 	filenameNode = malloc(sizeof(t_treenode));
// 	set_node_type(syntax_tree, NODE_REDIRECT_IN);
// 	set_node_type(filenameNode, NODE_FILE);
// 	set_node_data(syntax_tree, "<");
// 	set_node_data(filenameNode, filename);
// 	printf("filename is %s\n", filename);
// 	attach_tree_branch(syntax_tree, filenameNode, simplecmdNode);
// 	return (syntax_tree);
// }

// t_treenode	*cmd2(t_treenode *syntax_tree, t_curtok *curtok)		/* <simple command> '>' <filename> */
// {
// 	t_treenode	*simplecmdNode;
// 	t_treenode	*filenameNode;
// 	char		*filename;

// 	printf("i am in cmd2\n");
// 	simplecmdNode = simplecmd(syntax_tree, curtok);
// 	if (simplecmdNode == NULL)
// 		return (NULL);
// 	if (!term(CHAR_GREATER, NULL, curtok))
// 	{
// 		delete_node(simplecmdNode);
// 		return (NULL);
// 	}
// 	if (!term(TOKEN, &filename, curtok))
// 	{
// 		free(filename);
// 		delete_node(simplecmdNode);
// 		return (NULL);
// 	}
// 	syntax_tree = malloc(sizeof(t_treenode));
// 	filenameNode = malloc(sizeof(t_treenode));
// 	set_node_type(syntax_tree, NODE_REDIRECT_OUT);
// 	set_node_type(filenameNode, NODE_FILE);
// 	set_node_data(syntax_tree, ">");
// 	set_node_data(filenameNode, filename);
// 	printf("filename is %s\n", filename);
// 	attach_tree_branch(syntax_tree, filenameNode, simplecmdNode);
// 	return (syntax_tree);
// }

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

t_treenode	*cmd4(t_treenode *syntax_tree, t_curtok *curtok)
{
	// printf("i am in cmd4\n");
	return(simplecmd(syntax_tree, curtok));
}