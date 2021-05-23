#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*simplecmd(t_curtok *curtok)
{
	t_treenode	*tokenlistNode;
	t_treenode	*root;
	char		*pathname;

	if (!term(TOKEN, &pathname, curtok))
		return (NULL);
	tokenlistNode = tokenlist(curtok);
	root = malloc(sizeof(*root));
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
	t_treenode	*argNode;
	t_treenode	*root;
	char		*arg;
	char		*var_arg;
	int			res;

	if (!term(TOKEN, &arg, curtok))
		return (NULL);
	tokenlistNode = tokenlist(curtok);
	root = malloc(sizeof(*root));
	res = handle_vars_and_args(arg);
	// printf("res is %d\n", res);
	arg = strip_quotes(arg);
	if (res == 0)
	{
		set_node_data_type(root, arg, NODE_ARG);
		attach_tree_branch(root, tokenlistNode, NULL);
	}
	else if (res == 1)
	{
		set_node_data_type(root, arg, NODE_VAR);
		attach_tree_branch(root, tokenlistNode, NULL);
	}
	else
	{
		set_node_data_type(root, "$?", NODE_VAR);
		argNode = malloc(sizeof(*argNode));
		var_arg = create_arg(arg);
		set_node_data_type(argNode, var_arg, NODE_ARG);
		attach_tree_branch(root, argNode, NULL);
	}
	return (root);
}

t_treenode	*tokenlist2(void)
{
	return (NULL);
}
