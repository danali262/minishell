#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*command_line(t_curtok *curtok)
{
	t_treenode *node;

	if ((node = command_line1(curtok)) != NULL)
		return (node);
	if ((node = command_line2(curtok)) != NULL)
		return (node);
	if ((node = command_line3(curtok)) != NULL)
		return (node);
	return (NULL);
}

t_treenode	*command_line1(t_curtok *curtok)		/* <job> ';' <command line> */
{
	t_treenode	*jobNode;
	t_treenode	*cmdlineNode;
	t_treenode	*result;

	jobNode = job(curtok);
	if (jobNode == NULL)
		return (NULL);
	if (!term(CHAR_SEMICOLON, NULL, curtok->current_token))
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
	result = malloc(sizeof(t_treenode));
	set_node_type(result, NODE_SEMI);
	attach_tree_branch(result, jobNode, cmdlineNode);
	return (result);
}

t_treenode	*command_line2(t_curtok *curtok)	/* <job> ';' */
{
	t_treenode	*jobNode;
	t_treenode	*result;

	jobNode = job(curtok);
	if (jobNode == NULL)
		return (NULL);
	if (!term(CHAR_SEMICOLON, NULL, curtok->current_token))
	{
		delete_node(jobNode);
		return (NULL);
	}
	result = malloc(sizeof(t_treenode));
	set_node_type(result, NODE_SEMI);
	attach_tree_branch(result, jobNode, NULL);
	return (result);
}

t_treenode	*command_line3(t_curtok *curtok)	/* <job> */
{
	return(job(curtok));
}
