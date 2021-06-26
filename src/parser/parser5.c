#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*simplecmd(t_curtok *curtok)
{
	t_treenode	*tokenlistNode;
	t_treenode	*root;
	char		*pathname;

	pathname = NULL;
	if (!term(TOKEN, &pathname, curtok, NULL))
	{
		delete_node(&root);
		return (NULL);
	}
	tokenlistNode = tokenlist(curtok);
	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	set_node_data_type(root, pathname, NODE_PATH);
	attach_tree_branch(root, tokenlistNode, NULL);
	free(pathname);
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

	arg = NULL;
	if (!term(TOKEN, &arg, curtok, NULL))
		return (NULL);
	tokenlistNode = tokenlist(curtok);
	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	set_node_data_type(root, arg, NODE_ARG);
	attach_tree_branch(root, tokenlistNode, NULL);
	free(arg);
	return (root);
}

t_treenode	*tokenlist2(void)
{
	return (NULL);
}
