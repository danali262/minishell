#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*job(t_curtok *curtok)
{
	t_treenode	*node;
	t_token		*save;

	save = curtok->current_token;
	curtok->current_token = save;
	node = job1(curtok);
	if (node != NULL)
		return (node);
	curtok->current_token = save;
	node = job2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_treenode	*job1(t_curtok *curtok)
{
	t_treenode	*cmdNode;
	t_treenode	*jobNode;
	t_treenode	*root;

	cmdNode = cmd(curtok);
	if (cmdNode == NULL)
		return (NULL);
	if (!term(CHAR_PIPE, NULL, curtok, cmdNode))
	{
		// delete_node(&cmdNode);
		return (NULL);
	}
	jobNode = job(curtok);
	if (jobNode == NULL)
	{
		delete_node(&cmdNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	set_node_data_type(root, "|", NODE_PIPE);
	attach_tree_branch(root, cmdNode, jobNode);
	return (root);
}

t_treenode	*job2(t_curtok *curtok)
{
	return (cmd(curtok));
}
