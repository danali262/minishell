#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*cmd(t_curtok *curtok)
{
	t_treenode	*node;
	t_token		*save;

	save = curtok->current_token;
	curtok->current_token = save;
	node = cmd1(curtok);
	if (node != NULL)
		return (node);
	curtok->current_token = save;
	node = cmd2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_treenode	*cmd1(t_curtok *curtok)		/* <simple command> <redirection list> */
{
	t_treenode	*simplecmdNode;
	t_treenode	*root;
	t_treenode	*redirNode;
	char		*operator;

	simplecmdNode = simplecmd(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_REDIR, &operator, curtok, simplecmdNode))
	{
		delete_node(&simplecmdNode);
		return (NULL);
	}
	redirNode = redirlist(curtok);
	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	if (ft_strcmp(operator, ">") == 0)
		set_node_data_type(root, operator, NODE_REDIRECT_OUT);
	else if (ft_strcmp(operator, "<") == 0)
		set_node_data_type(root, operator, NODE_REDIRECT_IN);
	else
		set_node_data_type(root, operator, NODE_APPEND);
	attach_tree_branch(root, simplecmdNode, redirNode);
	return (root);
}

t_treenode	*cmd2(t_curtok *curtok)		/* <simple command> */
{
	return (simplecmd(curtok));
}
