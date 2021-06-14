#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*redirlist(t_curtok *curtok)
{
	t_treenode	*node;
	t_token		*save;

	save = curtok->current_token;
	curtok->current_token = save;
	node = redirlist1(curtok);
	if (node != NULL)
		return (node);
	curtok->current_token = save;
	node = redirlist2(curtok);
	if (node != NULL)
		return (node);
	node = redirlist3();
	if (node != NULL)
		return (node);
	return (NULL);
}

t_treenode	*redirlist1(t_curtok *curtok)	/* <redirection> <redirection list> */
{
	t_treenode	*redirlistNode;
	t_treenode	*root;
	char		*operator;
	char		*filename;

	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	if (!term(TOKEN, &filename, curtok, root))
	{
		delete_node(&root);
		return (NULL);
	}
	if (!term(CHAR_REDIR, &operator, curtok, root))
	{
		delete_node(&root);
		return (NULL);
	}
	redirlistNode = redirlist(curtok);
	if (redirlistNode == NULL)
		return (NULL);
	if (ft_strcmp(operator, "<") == 0)
		root = multiple_redirection_create_root(root, redirlistNode, filename, 1);
	else if (ft_strcmp(operator, ">") == 0)
		root = multiple_redirection_create_root(root, redirlistNode, filename, 2);
	else
		root = multiple_redirection_create_root(root, redirlistNode, filename, 3);
	return (root);
}

t_treenode	*redirlist2(t_curtok *curtok)	/* <redirection> <filenames> */
{
<<<<<<< HEAD
	t_treenode	*root;
	t_treenode	*fileNode_right;
	char		*operator;
	char		*filename_left;
	char		*filename_right;

	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	if (!term(TOKEN, &filename_left, curtok, root))
	{
		delete_node(&root);
		return (NULL);
	}
	if (!term(CHAR_REDIR, &operator, curtok, root))
	{
		delete_node(&root);
		return (NULL);
	}
	if (!term(TOKEN, &filename_right, curtok, root))
	{
		delete_node(&root);
		return (NULL);
	}
	fileNode_right = malloc(sizeof(*fileNode_right));
	if (!fileNode_right)
		parser_error(fileNode_right);
	set_node_data_type(fileNode_right, filename_right, NODE_FILE);
	if (ft_strcmp(operator, "<") == 0)
		root = multiple_redirection_create_root(root, fileNode_right, filename_left, 1);
	else if (ft_strcmp(operator, ">") == 0)
		root = multiple_redirection_create_root(root, fileNode_right, filename_left, 2);
	else
		root = multiple_redirection_create_root(root, fileNode_right, filename_left, 3);
	return (root);
=======
//	arg = strip_quotes(arg, root);
	set_node_data_type(root, arg, NODE_ARG);
	attach_tree_branch(root, tokenlist, NULL);
}

void	handle_node_var(t_treenode *root, t_treenode *tokenlist, char *arg)
{
//	arg = strip_quotes(arg, root);
	set_node_data_type(root, arg, NODE_VAR);
	attach_tree_branch(root, tokenlist, NULL);
>>>>>>> lexer_quotes
}

t_treenode	*redirlist3(void)
{
<<<<<<< HEAD
	return (NULL);
=======
	t_treenode	*argNode;
	char		*var_arg;

	// arg = strip_quotes(arg, root);
	set_node_data_type(root, "$?", NODE_VAR);
	argNode = malloc(sizeof(*argNode));
	if (!argNode)
		parser_error(argNode);
	var_arg = create_arg(arg, argNode);
	set_node_data_type(argNode, var_arg, NODE_ARG);
	attach_tree_branch(root, argNode, NULL);
>>>>>>> lexer_quotes
}
