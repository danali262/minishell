#include "lexer/lexer.h"
#include "parser.h"

<<<<<<< HEAD
t_treenode	*job(t_curtok *curtok)
{
	t_treenode	*node;
	t_token		*save;

	save = curtok->current_token;
	curtok->current_token = save;
	node = job1(curtok);
	if (node != NULL)
		return (node);
	curtok->current_token = save;
	node = job2(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_treenode	*job1(t_curtok *curtok)
{
	t_treenode	*cmdNode;
	t_treenode	*jobNode;
	t_treenode	*root;

	cmdNode = cmd(curtok);
	if (cmdNode == NULL)
		return (NULL);
	if (!term(CHAR_PIPE, NULL, curtok))
	{
		delete_node(cmdNode);
		return (NULL);
	}
	jobNode = job(curtok);
	if (jobNode == NULL)
	{
		delete_node(cmdNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	set_node_data_type(root, "|", NODE_PIPE);
	attach_tree_branch(root, cmdNode, jobNode);
	return (root);
}

t_treenode	*job2(t_curtok *curtok)
{
	return (cmd(curtok));
=======
t_treenode	*job(t_treenode *syntax_tree, t_curtok *curtok)
{
	// printf("i am in job\n");
	// if ((syntax_tree = job1(syntax_tree, curtok)) != NULL)
	// 	return (syntax_tree);
	if ((syntax_tree = job2(syntax_tree, curtok)) != NULL)
		return (syntax_tree);
	return (NULL);
}

// t_treenode	*job1(t_treenode *syntax_tree, t_curtok *curtok)		/* <command> '|' <job> */
// {
// 	t_treenode	*cmdNode;
// 	t_treenode	*jobNode;

// 	printf("i am in job1\n");
// 	cmdNode = cmd(syntax_tree, curtok);
// 	if (cmdNode == NULL)
// 		return (NULL);
// 	if (!term(CHAR_PIPE, NULL, curtok))
// 	{
// 		delete_node(cmdNode);
// 		return (NULL);
// 	}
// 	jobNode = job(syntax_tree, curtok);
// 	if (jobNode == NULL)
// 	{
// 		delete_node(cmdNode);
// 		return (NULL);
// 	}
// 	syntax_tree = malloc(sizeof(t_treenode));
// 	set_node_type(syntax_tree, NODE_PIPE);
// 	set_node_data(syntax_tree, "|");
// 	attach_tree_branch(syntax_tree, cmdNode, jobNode);
// 	return (syntax_tree);
// }

t_treenode	*job2(t_treenode *syntax_tree, t_curtok *curtok)		/*  <command> */
{
	// printf("i am in job2\n");
	return(cmd(syntax_tree, curtok));
>>>>>>> 7cc7773d618f9f601bdb0e9eada90eb52b29bfc3
}
