#include "lexer/lexer.h"
#include "parser.h"

<<<<<<< HEAD
t_treenode	*command_line(t_curtok *curtok)
{
	t_treenode	*node;
	t_token		*save;

	save = curtok->current_token;
	curtok->current_token = save;
	node = command_line1(curtok);
	if (node != NULL)
		return (node);
	curtok->current_token = save;
	node = command_line2(curtok);
	if (node != NULL)
		return (node);
	curtok->current_token = save;
	node = command_line3(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_treenode	*command_line1(t_curtok *curtok)
{
	t_treenode	*jobNode;
	t_treenode	*cmdlineNode;
	t_treenode	*root;

	jobNode = job(curtok);
	if (jobNode == NULL)
		return (NULL);
	if (!term(CHAR_SEMICOLON, NULL, curtok))
	{
		delete_node(jobNode);
		return (NULL);
	}
	cmdlineNode = command_line(curtok);
	if (cmdlineNode == NULL)
	{
		delete_node(jobNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	set_node_data_type(root, ";", NODE_SEMI);
	attach_tree_branch(root, jobNode, cmdlineNode);
	return (root);
}

t_treenode	*command_line2(t_curtok *curtok)
{
	t_treenode	*jobNode;
	t_treenode	*root;

	jobNode = job(curtok);
	if (jobNode == NULL)
		return (NULL);
	if (!term(CHAR_SEMICOLON, NULL, curtok))
	{
		delete_node(jobNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	set_node_data_type(root, ";", NODE_SEMI);
	attach_tree_branch(root, jobNode, NULL);
	return (root);
}

t_treenode	*command_line3(t_curtok *curtok)
{
	return (job(curtok));
=======
t_treenode	*command_line(t_treenode *syntax_tree, t_curtok *curtok)
{
	// printf("I am in command line\n");
	// if ((syntax_tree = command_line1(syntax_tree, curtok)) != NULL)
	// 	return (syntax_tree);
	// if ((syntax_tree = command_line2(syntax_tree, curtok)) != NULL)
	// 	return (syntax_tree);
	if ((syntax_tree = command_line3(syntax_tree, curtok)) != NULL)
		return (syntax_tree);
	return (NULL);
}

// t_treenode	*command_line1(t_treenode *syntax_tree, t_curtok *curtok)		/* <job> ';' <command line> */
// {
// 	t_treenode	*jobNode;
// 	t_treenode	*cmdlineNode;

// 	printf("I am in command line1\n");
// 	jobNode = job(syntax_tree, curtok);
// 	if (jobNode == NULL)
// 		return (NULL);
// 	if (!term(CHAR_SEMICOLON, NULL, curtok))
// 	{
// 		delete_node(jobNode);
// 		return (NULL);
// 	}
// 	cmdlineNode = command_line(syntax_tree, curtok);
// 	if (cmdlineNode == NULL)
// 	{
// 		delete_node(jobNode);
// 		return (NULL);
// 	}
// 	syntax_tree = malloc(sizeof(t_treenode));
// 	set_node_type(syntax_tree, NODE_SEMI);
// 	set_node_data(syntax_tree, ";");
// 	attach_tree_branch(syntax_tree, jobNode, cmdlineNode);
	
// 	return (syntax_tree);
// }

// t_treenode	*command_line2(t_treenode *syntax_tree, t_curtok *curtok)	/* <job> ';' */
// {
// 	t_treenode	*jobNode;

// 	printf("I am in command line2\n");
// 	jobNode = job(syntax_tree, curtok);
// 	if (jobNode == NULL)
// 		return (NULL);
// 	if (!term(CHAR_SEMICOLON, NULL, curtok))
// 	{
// 		delete_node(jobNode);
// 		return (NULL);
// 	}
// 	syntax_tree = malloc(sizeof(t_treenode));
// 	set_node_type(syntax_tree, NODE_SEMI);
// 	set_node_data(syntax_tree, ";");
// 	attach_tree_branch(syntax_tree, jobNode, NULL);
// 	return (syntax_tree);
// }

t_treenode	*command_line3(t_treenode *syntax_tree, t_curtok *curtok)	/* <job> */
{
	// printf("I am in command line3\n");
	return(job(syntax_tree, curtok));
>>>>>>> 7cc7773d618f9f601bdb0e9eada90eb52b29bfc3
}
