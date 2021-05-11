#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*simplecmd(t_treenode *syntax_tree, t_curtok *curtok)	/* <pathname> <token list> */
{
	t_treenode	*tokenlistNode;
	char		*pathname;

	printf("i am in simplecmd\n");
	if (!term(TOKEN, &pathname, curtok))
		return (NULL);
	syntax_tree = malloc(sizeof(t_treenode));
	set_node_type(syntax_tree, NODE_PATH);
	set_node_data(syntax_tree, pathname);
	printf("pathname is %s\n", pathname);
	while (curtok->current_token && curtok->current_token->type != 60 && curtok->current_token->type != 62)
	{
		printf("current token is %s\n", curtok->current_token->data);
		printf("current token type is %d\n", curtok->current_token->type);
		tokenlistNode = tokenlist(syntax_tree, curtok);
		add_child_node(syntax_tree, tokenlistNode);			
	}
	return (syntax_tree);
}

t_treenode	*tokenlist(t_treenode *syntax_tree, t_curtok *curtok)
{
	printf("i am in tokenlist\n");
	if ((syntax_tree = tokenlist1(syntax_tree, curtok)) != NULL)
		return (syntax_tree);
	if ((syntax_tree = tokenlist2()) != NULL)
		return (syntax_tree);
	return (NULL);
}

t_treenode	*tokenlist1(t_treenode *syntax_tree, t_curtok *curtok)	/* <token> <token_list> */
{
	char		*arg;

	printf("i am in tokenlist1\n");
	// printf("current token in tokenlist is %s\n", curtok->current_token->data);
	if(!term(TOKEN, &arg, curtok))
		return (NULL);
	syntax_tree = malloc(sizeof(t_treenode));
	set_node_type(syntax_tree, NODE_ARG);
	set_node_data(syntax_tree, arg);
	printf("arg is %s\n", arg);
	return (syntax_tree);
}

t_treenode	*tokenlist2(void)
{
	printf("i am in tokenlist2\n");
	return (NULL);
}
