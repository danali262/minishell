#include "redirection.h"

static void	assign_file_multiple(t_treenode *syntax_tree, t_shell *shell, int
		type)
{
	if (type == NODE_REDIRECT_IN)
		shell->redir->filename_in = ft_strdup(syntax_tree->data);
	else if (type == NODE_REDIRECT_OUT)
		shell->redir->filename_out = ft_strdup(syntax_tree->data);
	else
		shell->redir->filename_app = ft_strdup(syntax_tree->data);
}

static void	check_node_type(t_treenode *node, t_shell *shell)
{
	if (node->type == NODE_REDIRECT_IN)
		shell->redir->redirect_in = 1;
	if (node->type == NODE_REDIRECT_OUT)
		shell->redir->redirect_out = 1;
	if (node->type == NODE_APPEND)
		shell->redir->redirect_app = 1;
}

static void	handle_multiple_append(t_treenode *node, int saved_type, t_shell
	*shell)
{
	int	fd;

	assign_file_multiple(node->left, shell, saved_type);
	assign_file_multiple(node->right, shell, node->type);
	if (node->type == NODE_REDIRECT_OUT)
	{
		fd = open(shell->redir->filename_app, O_WRONLY | O_CREAT,
				0666);
		close(fd);
		shell->redir->redirect_app = 0;
	}
}

static void	execute_multiple_redirection(t_treenode *node, t_shell *shell)
{
	if (shell->redir->saved_nodetype == NODE_APPEND || node->type == NODE_APPEND)
		handle_multiple_append(node, shell->redir->saved_nodetype, shell);
	else
	{
		assign_file_multiple(node->left, shell, shell->redir->saved_nodetype);
		assign_file_multiple(node->right, shell, node->type);
	}
}

void	multiple_redirection(t_treenode *syntax_tree, t_shell *shell)
{
	int	i;

	i = 0;
	check_node_type(syntax_tree, shell);
	shell->redir->saved_nodetype = syntax_tree->type;
	syntax_tree = syntax_tree->right;
	i++;
	while (i < shell->redir->redir_nbr)
	{
		check_node_type(syntax_tree, shell);
		i++;
		if (syntax_tree->right->type == NODE_REDIRECT_IN
			|| syntax_tree->right->type == NODE_REDIRECT_OUT
			|| syntax_tree->right->type == NODE_APPEND)
		{
			syntax_tree = syntax_tree->right;
			continue ;
		}
		else
			execute_multiple_redirection(syntax_tree, shell);
	}
}
