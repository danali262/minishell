#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*simplecmd(t_curtok *curtok)
{
	t_treenode	*tokenlistNode;
	t_treenode	*root;
	char		*pathname;

	pathname = NULL;
	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	if (!term(TOKEN, &pathname, curtok, root))
	{
		free(root);
		free(pathname);
		return (NULL);
	}
	tokenlistNode = tokenlist(curtok);
	set_node_data_type(root, pathname, NODE_PATH);
	attach_tree_branch(root, tokenlistNode, NULL);
	return (root);
}

t_treenode	*tokenlist(t_curtok *curtok)
{
	t_treenode	*node;
	t_token		*save;

	save = curtok->current_token;
	curtok->current_token = save;
	node = tokenlist1(curtok);
	if (node != NULL)
		return (node);
	curtok->current_token = save;
	node = tokenlist2();
	if (node != NULL)
		return (node);
	return (NULL);
}

t_treenode	*tokenlist1(t_curtok *curtok)
{
	t_treenode	*tokenlistNode;
	t_treenode	*root;
	char		*arg;
	int			handle_node_result;

	arg = NULL;
	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	if (!term(TOKEN, &arg, curtok, root))
	{
		free(arg);
		free(root);
		return (NULL);
	}
	tokenlistNode = tokenlist(curtok);
	handle_node_result = handle_vars_and_args(arg);
	if (handle_node_result == 0)
		handle_node_arg(root, tokenlistNode, arg);
	else if (handle_node_result == 1)
		handle_node_var(root, tokenlistNode, arg);
	else
		handle_both_nodes(root, arg);
	return (root);
}

t_treenode	*tokenlist2(void)
{
	return (NULL);
}
