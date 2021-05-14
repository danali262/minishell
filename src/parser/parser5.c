#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*simplecmd(t_curtok *curtok)	/* <pathname> <token list> */
{
	t_treenode	*tokenlistNode;
	t_treenode	*root;
	char		*pathname;

	if (!term(TOKEN, &pathname, curtok))
		return (NULL);
	tokenlistNode = tokenlist(curtok);
	root = malloc(sizeof(*root));
	set_node_type(root, NODE_PATH);
	set_node_data(root, pathname);
	attach_tree_branch(root, tokenlistNode, NULL);
	return (root);
}

t_treenode	*tokenlist(t_curtok *curtok)
{
	t_treenode	*node;
	t_token		*save;

	save = curtok->current_token;
	curtok->current_token = save;
	if ((node = tokenlist1(curtok)) != NULL)
		return (node);
	curtok->current_token = save;
	if ((node = tokenlist2()) != NULL)
		return (node);
	return (NULL);
}

t_treenode	*tokenlist1(t_curtok *curtok)	/* <token> <token_list> */
{
	t_treenode	*tokenlistNode;
	t_treenode	*root;
	char		*arg;

	if(!term(TOKEN, &arg, curtok))
		return (NULL);
	tokenlistNode = tokenlist(curtok);
	root = malloc(sizeof(*root));
	set_node_type(root, NODE_ARG);
	set_node_data(root, arg);
	attach_tree_branch(root, tokenlistNode, NULL);
	return (root);
}

t_treenode	*tokenlist2(void)
{
	return (NULL);
}
