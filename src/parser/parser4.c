#include "lexer/lexer.h"
#include "parser.h"

static t_treenode	*cmd1_root(char *operator, t_treenode *simplecmdNode,
	t_treenode *redirNode)
{
	t_treenode	*root;

	root = ft_calloc(1, sizeof(*root));
	if (!root)
		parser_error(root);
	root = create_node(root, operator);
	attach_tree_branch(root, simplecmdNode, redirNode);
	free(operator);
	return (root);
}

t_treenode	*cmd1(t_curtok *curtok)
{
	t_treenode	*simplecmdNode;
	t_treenode	*redirNode;
	char		*operator;

	operator = NULL;
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
	{
		free(operator);
		delete_node(&simplecmdNode);
		return (NULL);
	}
	return (cmd1_root(operator, simplecmdNode, redirNode));
}

static t_treenode	*cmd2_root(t_treenode *simplecmdNode, char *operator,
	char *filename)
{
	t_treenode	*root;

	root = ft_calloc(1, sizeof(*root));
	if (!root)
		parser_error(root);
	root = handle_root_redirection(root, simplecmdNode, operator,
			filename);
	free(operator);
	free(filename);
	return (root);
}

t_treenode	*cmd2(t_curtok *curtok)
{
	t_treenode	*simplecmdNode;
	char		*filename;
	char		*operator;

	operator = NULL;
	filename = NULL;
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
		free(operator);
		delete_node(&simplecmdNode);
		return (NULL);
	}
	return (cmd2_root(simplecmdNode, operator, filename));
}

t_treenode	*cmd3(t_curtok *curtok)
{
	return (simplecmd(curtok));
}
