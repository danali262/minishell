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
	return (NULL);
}

t_treenode	*cmd1(t_curtok *curtok)
{
	t_treenode	*simplecmdNode;
	t_treenode	*root;
	t_treenode	*redirNode;
	char		*operator;

	simplecmdNode = simplecmd(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_REDIR, &operator, curtok, simplecmdNode))
	{
		delete_node(&simplecmdNode);
		return (NULL);
	}
	redirNode = redirlist(curtok);
	if (redirNode == NULL)
		return (NULL);
	root = malloc(sizeof(*root));
	if (!root)
		parser_error(root);
	root = create_node(root, operator);
	attach_tree_branch(root, simplecmdNode, redirNode);
	return (root);
}

t_treenode	*cmd2(t_curtok *curtok)
{
	t_treenode	*simplecmdNode;
	t_treenode	*root;
	char		*filename;
	char		*operator;

	simplecmdNode = simplecmd(curtok);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(CHAR_REDIR, &operator, curtok, simplecmdNode))
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
	root = handle_root_redirection(root, simplecmdNode, operator,
			filename);
	return (root);
}

t_treenode	*cmd3(t_curtok *curtok)
{
	return (simplecmd(curtok));
}
