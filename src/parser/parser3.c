#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*job(t_curtok *curtok)
{
	t_treenode	*node;
	t_token		*save;

	save = curtok->current_token;
	curtok->current_token = save;
	if ((node = job1(curtok)) != NULL)
		return (node);
	curtok->current_token = save;
	if ((node = job2(curtok)) != NULL)
		return (node);
	return (NULL);
}

t_treenode	*job1(t_curtok *curtok)		/* <command> '|' <job> */
{
	t_treenode	*cmdNode;
	t_treenode	*jobNode;
	t_treenode	*root;

	cmdNode = cmd(curtok);
	if (cmdNode == NULL)
		return (NULL);
	if (!term(CHAR_PIPE, NULL, curtok))
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
	root = malloc(sizeof(*root));
	set_node_type(root, NODE_PIPE);
	set_node_data(root, "|");
	attach_tree_branch(root, cmdNode, jobNode);
	return (root);
}

t_treenode	*job2(t_curtok *curtok)		/*  <command> */
{
	return(cmd(curtok));
}
