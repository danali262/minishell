#include "lexer/lexer.h"
#include "parser.h"

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
}
