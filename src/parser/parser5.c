#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*simplecmd(t_treenode *syntax_tree, t_curtok *curtok)	/* <pathname> <token list> */
{
	t_treenode	*tokenlistNode;
	char		*pathname;

	// printf("i am in simplecmd\n");
	if (!term(TOKEN, &pathname, curtok))
		return (NULL);
	syntax_tree = malloc(sizeof(t_treenode));
	set_node_type(syntax_tree, NODE_PATH);
	set_node_data(syntax_tree, pathname);
	printf("pathname is %s\n", pathname);
	while (curtok->current_token)
	{
		tokenlistNode = tokenlist(syntax_tree, curtok);
		if (tokenlistNode == NULL)
		{
			tokenlistNode = malloc(sizeof(t_treenode));
			set_node_type(tokenlistNode, NODE_EMPTY);
			set_node_data(tokenlistNode, "empty");
		}
		attach_tree_branch(syntax_tree, tokenlistNode, NULL);		/* consider making it a one branch function..? */
	}
	return (syntax_tree);
}

t_treenode	*tokenlist(t_treenode *syntax_tree, t_curtok *curtok)
{
	// printf("i am in tokenlist\n");
	if ((syntax_tree = tokenlist1(syntax_tree, curtok)) != NULL)
		return (syntax_tree);
	if ((syntax_tree = tokenlist2()) != NULL)
		return (syntax_tree);
	return (NULL);
}

t_treenode	*tokenlist1(t_treenode *syntax_tree, t_curtok *curtok)	/* <token> <token_list> */
{
	// t_treenode	*tokenlistNode;
	// t_treenode	*tokenNode;
	char		*arg;

	// printf("i am in tokenlist1\n");
	// printf("current token in tokenlist is %s\n", curtok->current_token->data);
	if(!term(TOKEN, &arg, curtok))
		return (NULL);
	// tokenlistNode = tokenlist(syntax_tree, curtok);
	syntax_tree = malloc(sizeof(t_treenode));
	// tokenNode = malloc(sizeof(t_treenode));
	set_node_type(syntax_tree, NODE_ARG);
	set_node_data(syntax_tree, arg);
	// set_node_type(tokenNode, NODE_ARG);
	// set_node_data(tokenNode, arg);
	printf("arg is %s\n", arg);
	// attach_tree_branch(syntax_tree, tokenNode, tokenlistNode);
	return (syntax_tree);
}

t_treenode	*tokenlist2(void)
{
	// printf("i am in tokenlist2\n");
	return (NULL);
}
