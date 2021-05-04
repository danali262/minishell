#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*cmd(t_curtok *curtok)
{
	t_treenode *node;

	if ((node = cmd1(curtok)) != NULL)
		return (node);
	if (node = cmd2(curtok) != NULL)
		return (node);
	if (node = cmd3(curtok) != NULL)
		return (node);
	if (node = cmd4(curtok) != NULL)
		return (node);
	return (NULL);
}

t_treenode	*cmd1(t_curtok *curtok)		/* <simple command> <redirection list> */
{
	t_treenode	*smplcmdNode;
	t_treenode	*redirlistNode;
	t_treenode	*result;

	smplcmdNode = cmd(curtok);
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

t_treenode	*job2(t_curtok *curtok)
{
	return(cmd(curtok));
}
