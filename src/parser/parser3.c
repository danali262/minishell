#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*job(t_curtok *curtok)
{
	t_treenode *node;

	if ((node = job1(curtok)) != NULL)
		return (node);
	if ((node = job2(curtok)) != NULL)
		return (node);
	return (NULL);
}

t_treenode	*job1(t_curtok *curtok)		/* <command> '|' <job> */
{
	t_treenode	*cmdNode;
	t_treenode	*jobNode;
	t_treenode	*result;

	cmdNode = cmd(curtok);
	if (cmdNode == NULL)
		return (NULL);
	if (!term(CHAR_PIPE, NULL, curtok->current_token))
	{
		delete_node(cmdNode);
		return (NULL);
	}
	jobNode = job(curtok);
	if (jobNode == NULL)
	{
		delete_node(cmdNode);
		return (NULL);
	}
	result = malloc(sizeof(t_treenode));
	set_node_type(result, NODE_PIPE);
	attach_tree_branch(result, cmdNode, jobNode);
	return (result);
}

t_treenode	*job2(t_curtok *curtok)		/*  <command> */
{
	return(cmd(curtok));
}
