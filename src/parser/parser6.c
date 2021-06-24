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

t_treenode	*redirlist1(t_curtok *curtok)
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
		free(root);
		free(filename);
		return (NULL);
	}
	if (!term(CHAR_REDIR, &operator, curtok, root))
		return (NULL);
	redirlistNode = redirlist(curtok);
	if (redirlistNode == NULL)
		return (NULL);
	root = handle_root_redirection_multiple(root, redirlistNode, operator,
			filename);
	return (root);
}

t_treenode	*redirlist2(t_curtok *curtok)
{
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
		free(root);
		free(filename_left);
		return (NULL);
	}
	if (!term(CHAR_REDIR, &operator, curtok, root))
	{
		free(root);
		return (NULL);
	}
	if (!term(TOKEN, &filename_right, curtok, root))
	{
		free(root);
		free(filename_right);
		return (NULL);
	}
	fileNode_right = malloc(sizeof(*fileNode_right));
	if (!fileNode_right)
		parser_error(fileNode_right);
	set_node_data_type(fileNode_right, filename_right, NODE_FILE);
	root = handle_root_redirection_multiple(root, fileNode_right, operator,
			filename_left);
	return (root);
}

t_treenode	*redirlist3(void)
{
	return (NULL);
}
