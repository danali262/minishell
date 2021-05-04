#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*simplecmd(t_curtok *curtok)	/* <pathname> <token list> */
{
	t_treenode	*tokenlistNode;
	t_treenode	*pathnameNode;
	t_treenode	*result;
	char		*pathname;

	if (!term(TOKEN, &pathname, curtok->current_token))
		return (NULL);
	tokenlistNode = TOKENLIST(curtok);
	result = malloc(sizeof(t_treenode));
	pathnameNode = malloc(sizeof(t_treenode));
	set_node_type(result, NODE_CMD);
	set_node_type(pathnameNode, NODE_PATH);
	set_node_data(pathnameNode, pathname);
	attach_tree_branch(result, pathnameNode, tokenlistNode);
	return (result);
}

