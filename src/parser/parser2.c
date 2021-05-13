#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*command_line(t_curtok *curtok)
{
	t_treenode	*node;
	t_token		*save;

	save = curtok->current_token;
	curtok->current_token = save;
	if ((node = command_line1(curtok)) != NULL)
		return (node);
	curtok->current_token = save;
	if ((node = command_line2(curtok)) != NULL)
		return (node);
	curtok->current_token = save;
	if ((node = command_line3(curtok)) != NULL)
		return (node);
	return (NULL);
}

t_treenode	*command_line1(t_curtok *curtok)		/* <job> ';' <command line> */
{
	t_treenode	*jobNode;
	t_treenode	*cmdlineNode;
	t_treenode	*root;

	// printf("i am in command line 1\n");
	jobNode = job(curtok);
	if (jobNode == NULL)
		return (NULL);
	if (!term(CHAR_SEMICOLON, NULL, curtok))
	{
		delete_node(jobNode);
		return (NULL);
	}
	cmdlineNode = command_line(curtok);
	if (cmdlineNode == NULL)
	{
		delete_node(jobNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	set_node_type(root, NODE_SEMI);
	set_node_data(root, ";");
	printf("0. WE ATTACH TO %s: LEFT %s and RIGHT %s\n", root->data, jobNode->data, cmdlineNode->data);
	attach_tree_branch(root, jobNode, cmdlineNode);
	return (root);
}

t_treenode	*command_line2(t_curtok *curtok)	/* <job> ';' */
{
	t_treenode	*jobNode;
	t_treenode	*root;

	// printf("i am in command line 2\n");
	jobNode = job(curtok);
	if (jobNode == NULL)
		return (NULL);
	if (!term(CHAR_SEMICOLON, NULL, curtok))
	{
		delete_node(jobNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	set_node_type(root, NODE_SEMI);
	set_node_data(root, ";");
	printf("1. WE ATTACH TO %s: LEFT %s and RIGHT NULL\n", root->data, jobNode->data);
	attach_tree_branch(root, jobNode, NULL);
	return (root);
}

t_treenode	*command_line3(t_curtok *curtok)	/* <job> */
{
	// printf("i am in command line 3\n");
	return(job(curtok));
}
