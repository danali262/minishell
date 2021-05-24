#include "lexer/lexer.h"
#include "parser.h"

t_treenode	*cmd(t_curtok *curtok)
{
	t_treenode	*node;
	t_token		*save;

	save = curtok->current_token;
	curtok->current_token = save;
	node = cmd1(curtok);
	if (node != NULL)
		return (node);
	curtok->current_token = save;
	node = cmd2(curtok);
	if (node != NULL)
		return (node);
	curtok->current_token = save;
	node = cmd3(curtok);
	if (node != NULL)
		return (node);
	curtok->current_token = save;
	node = cmd4(curtok);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_treenode	*cmd1(t_curtok *curtok)		/* <simple command> '<' <filename> */
{
	t_treenode	*simplecmdNode;
	t_treenode	*root;
	char		*filename;

	simplecmdNode = simplecmd(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_LESSER, NULL, curtok, simplecmdNode))
	{
		delete_node(&simplecmdNode);
		return (NULL);
	}
	if (!term(TOKEN, &filename, curtok, simplecmdNode))
	{
		free(filename);
		delete_node(&simplecmdNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	root = redirection_create_root(root, simplecmdNode, filename, 1);
	return (root);
}

t_treenode	*cmd2(t_curtok *curtok)		/* <simple command> '>' <filename> */
{
	t_treenode	*simplecmdNode;
	t_treenode	*root;
	char		*filename;

	simplecmdNode = simplecmd(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_GREATER, NULL, curtok, simplecmdNode))
	{
		delete_node(&simplecmdNode);
		return (NULL);
	}
	if (!term(TOKEN, &filename, curtok, simplecmdNode))
	{
		free(filename);
		delete_node(&simplecmdNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	root = redirection_create_root(root, simplecmdNode, filename, 2);
	return (root);
}

t_treenode	*cmd3(t_curtok *curtok)		/* <simple command> '>>' <filename> */
{
	t_treenode	*simplecmdNode;
	t_treenode	*root;
	char		*filename;

	simplecmdNode = simplecmd(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_APPEND, NULL, curtok, simplecmdNode))
	{
		delete_node(&simplecmdNode);
		return (NULL);
	}
	if (!term(TOKEN, &filename, curtok, simplecmdNode))
	{
		free(filename);
		delete_node(&simplecmdNode);
		return (NULL);
	}
	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	root = redirection_create_root(root, simplecmdNode, filename, 3);
	return (root);
}

t_treenode	*cmd4(t_curtok *curtok)
{
	return (simplecmd(curtok));
}
