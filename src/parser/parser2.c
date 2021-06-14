#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*command_line(t_curtok *curtok)
{
	t_treenode	*node;
	t_token		*save;

	save = curtok->current_token;
	curtok->current_token = save;
	node = command_line1(curtok);
	if (node != NULL)
		return (node);
	curtok->current_token = save;
	node = command_line2(curtok);
	if (node != NULL)
		return (node);
	curtok->current_token = save;
	node = command_line3(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_treenode	*command_line1(t_curtok *curtok)	/* <job>';'<command line> */
{
	t_treenode	*jobNode;
	t_treenode	*cmdlineNode;
	t_treenode	*root;

	jobNode = job(curtok);
	if (jobNode == NULL)
		return (NULL);
	if (!term(CHAR_SEMICOLON, NULL, curtok, jobNode))
	{
		delete_node(&jobNode);
		return (NULL);
	}
	cmdlineNode = command_line(curtok);
	if (cmdlineNode == NULL)
	{
		delete_node(&jobNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	set_node_data_type(root, ";", NODE_SEMI);
	attach_tree_branch(root, jobNode, cmdlineNode);
	return (root);
}

t_treenode	*command_line2(t_curtok *curtok)	/* <job> ';' */
{
	t_treenode	*jobNode;
	t_treenode	*root;

	jobNode = job(curtok);
	if (jobNode == NULL)
		return (NULL);
	if (!term(CHAR_SEMICOLON, NULL, curtok, jobNode))
	{
		delete_node(&jobNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	set_node_data_type(root, ";", NODE_SEMI);
	attach_tree_branch(root, jobNode, NULL);
	return (root);
}

t_treenode	*command_line3(t_curtok *curtok)	/* <job> */
{
	return (job(curtok));
}
