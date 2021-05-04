#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*job(t_curtok *curtok)
{
	t_treenode *node;

	if ((node = job1(curtok)) != NULL)
		return (node);
	if (node = job2(curtok) != NULL)
		return (node);
	return (NULL);
}

t_treenode	*command_line1(t_curtok *curtok)		/* <job> ';' <command line> */
{
	t_treenode	*jobNode;
	t_treenode	*cmdlineNode;
	t_treenode	*result;	/* shouldn't the result be the parent of jobNode and cmdlineNode? */

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

t_treenode	*command_line3(t_curtok *curtok)
{
	return(job(curtok));
}
