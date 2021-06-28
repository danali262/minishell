#include "redirection.h"
#include "../shell_utilities.h"

static void	check_node_type(t_treenode *node, t_shell *shell)
{
	if (node->type == NODE_REDIRECT_IN)
		shell->redir->redirect_in = 1;
	if (node->type == NODE_REDIRECT_OUT)
		shell->redir->redirect_out = 1;
	if (node->type == NODE_APPEND)
		shell->redir->redirect_app = 1;
}

static void	turn_off_redirect_flag(t_treenode *node, t_shell *shell)
{
	if (node->type == NODE_REDIRECT_IN)
		shell->redir->redirect_in = 0;
	if (node->type == NODE_REDIRECT_OUT)
		shell->redir->redirect_out = 0;
	if (node->type == NODE_APPEND)
		shell->redir->redirect_app = 0;
}

static void	execute_multiple_redirection(t_treenode *node, t_shell *shell)
{
	int	fd;

	if (shell->redir->redir_nbr > 2)
	{
		fd = open(node->left->data, O_WRONLY | O_CREAT,
				0777);
		close(fd);
		assign_file_multiple(node->right, shell, node->type);
	}
	if (shell->redir->saved_nodetype == NODE_APPEND || node->type
		== NODE_APPEND)
		handle_multiple_append(node, shell->redir->saved_nodetype,
			shell);
	else
	{
		assign_file_multiple(node->left, shell, shell->redir->saved_nodetype);
		assign_file_multiple(node->right, shell, node->type);
	}
}

void	multiple_redirection(t_treenode *syntax_tree, t_shell *shell)
{
	int	i;
	int	fd;

	i = 0;
	check_node_type(syntax_tree, shell);
	shell->redir->saved_nodetype = syntax_tree->type;
	syntax_tree = syntax_tree->right;
	i++;
	while (i < shell->redir->redir_nbr)
	{
		check_node_type(syntax_tree, shell);
		i++;
		if (is_redirect_node(syntax_tree->right))
		{
			fd = open(syntax_tree->left->data, O_WRONLY | O_CREAT,
					0777);
			close(fd);
			turn_off_redirect_flag(syntax_tree, shell);
			syntax_tree = syntax_tree->right;
			continue ;
		}
		else
			execute_multiple_redirection(syntax_tree, shell);
	}
}
