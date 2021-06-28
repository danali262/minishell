#include "lexer/lexer.h"
#include "parser.h"

static t_treenode	*redirlist1_root(t_treenode *redirlistNode, char *operator,
	char *filename)
{
	t_treenode	*root;

	root = ft_calloc(1, sizeof(*root));
	if (!root)
		parser_error(root);
	root = handle_root_redirection_multiple(root, redirlistNode, operator,
			filename);
	free(filename);
	free(operator);
	return (root);
}

t_treenode	*redirlist1(t_curtok *curtok)
{
	t_treenode	*redirlistNode;
	char		*operator;
	char		*filename;

	operator = NULL;
	filename = NULL;
	if (!term(TOKEN, &filename, curtok, NULL))
		return (NULL);
	if (!term(CHAR_REDIR, &operator, curtok, NULL))
	{
		free(filename);
		return (NULL);
	}
	redirlistNode = redirlist(curtok);
	if (redirlistNode == NULL)
	{
		free(filename);
		free(operator);
		return (NULL);
	}
	return (redirlist1_root(redirlistNode, operator, filename));
}

static t_treenode	*redirlist2_root(char *filename_right, char *operator, char
	*filename_left)
{
	t_treenode	*root;
	t_treenode	*fileNode_right;

	fileNode_right = ft_calloc(1, sizeof(*fileNode_right));
	if (!fileNode_right)
		parser_error(fileNode_right);
	set_node_data_type(fileNode_right, filename_right, NODE_FILE);
	root = ft_calloc(1, sizeof(*root));
	if (!root)
		parser_error(root);
	root = handle_root_redirection_multiple(root, fileNode_right, operator,
			filename_left);
	free(filename_right);
	free(filename_left);
	free(operator);
	return (root);
}

t_treenode	*redirlist2(t_curtok *curtok)
{
	char		*operator;
	char		*filename_left;
	char		*filename_right;

	operator = NULL;
	filename_left = NULL;
	filename_right = NULL;
	if (!term(TOKEN, &filename_left, curtok, NULL))
		return (NULL);
	if (!term(CHAR_REDIR, &operator, curtok, NULL))
	{
		free(filename_left);
		return (NULL);
	}
	if (!term(TOKEN, &filename_right, curtok, NULL))
	{
		free(filename_left);
		free(operator);
		return (NULL);
	}
	return (redirlist2_root(filename_right, operator, filename_left));
}

t_treenode	*redirlist3(void)
{
	return (NULL);
}
