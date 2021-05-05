#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*simplecmd(t_curtok *curtok)	/* <pathname> <token list> */
{
	t_treenode	*tokenlistNode;
	t_treenode	*pathnameNode;
	t_treenode	*result;
	char		pathname;

	if (!term(TOKEN, &pathname, curtok->current_token))
		return (NULL);
	tokenlistNode = tokenlist(curtok);
	result = malloc(sizeof(t_treenode));
	pathnameNode = malloc(sizeof(t_treenode));
	set_node_type(result, NODE_CMD);
	set_node_type(pathnameNode, NODE_PATH);
	set_node_data(pathnameNode, &pathname);
	attach_tree_branch(result, pathnameNode, tokenlistNode);
	return (result);
}

t_treenode	*tokenlist(t_curtok *curtok)
{
	t_treenode	*node;

	if ((node = tokenlist1(curtok)) != NULL)
		return (node);
	if ((node = tokenlist2()) != NULL)
		return (node);
	return (NULL);
}

t_treenode	*tokenlist1(t_curtok *curtok)	/* <token> <token_list> */
{
	t_treenode	*tokenlistNode;
	t_treenode	*tokenNode;
	t_treenode	*result;
	char		arg;

	if(!term(TOKEN, &arg, curtok->current_token))
		return (NULL);
	tokenlistNode = tokenlist(curtok);
	result = malloc(sizeof(t_treenode));
	tokenNode = malloc(sizeof(t_treenode));
	set_node_type(result, NODE_TOKEN);
	set_node_type(tokenNode, NODE_ARG);
	set_node_data(tokenNode, &arg);
	attach_tree_branch(result, tokenNode, tokenlistNode);
	return (result);
}

t_treenode	*tokenlist2(void)
{
	return (NULL);
}
