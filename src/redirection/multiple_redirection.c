#include "redirection.h"
#include "../shell_utilities.h"

static t_treenode	*handle_redirect_node(t_treenode *node, t_shell *shell)
{
	if (!(shell->redir->filename_in) || (ft_strcmp(node->left->data,
				shell->redir->filename_in)))
		handle_redirect_node_execution(node, shell);
	if (node->type == NODE_REDIRECT_IN)
		shell->redir->redirect_in = 0;
	if (node->type == NODE_REDIRECT_OUT)
		shell->redir->redirect_out = 0;
	if (node->type == NODE_APPEND)
		shell->redir->redirect_app = 0;
	shell->redir->last_nodetype = node->type;
	return (node->right);
}

static void	more_than_two_redir(t_treenode *node, t_shell *shell)
{
	if (shell->redir->first_nodetype == NODE_REDIRECT_OUT && node->type
		== NODE_APPEND)
		shell->redir->redirect_out = 0;
	if (shell->redir->first_nodetype == NODE_APPEND && node->type
		== NODE_REDIRECT_OUT)
		shell->redir->redirect_app = 0;
	handle_redirect_node_execution(node, shell);
	assign_file_multiple(node->right, shell, node->type);
}

static void	two_redir_not_append(t_treenode *node, t_shell *shell)
{
	int	fd;

	if (shell->redir->first_nodetype == node->type)
	{			
		fd = open(node->left->data, O_WRONLY | O_CREAT | O_TRUNC,
				0666);
		close(fd);
		assign_file_multiple(node->right, shell, node->type);
	}
	else
	{
		assign_file_multiple(node->left, shell,
			shell->redir->first_nodetype);
		assign_file_multiple(node->right, shell, node->type);
	}
}

static void	execute_multiple_redirection(t_treenode *node, t_shell *shell)
{
	if (shell->redir->redir_nbr > 2)
		more_than_two_redir(node, shell);
	else
	{
		if (shell->redir->first_nodetype == NODE_APPEND || node->type
			== NODE_APPEND)
			handle_multiple_append(node, shell->redir->first_nodetype,
				shell);
		else
			two_redir_not_append(node, shell);
	}
}

int	multiple_redirection(t_treenode *syntax_tree, t_shell *shell)
{
	int	i;

	i = 0;
	check_node_type(syntax_tree, shell);
	shell->redir->first_nodetype = syntax_tree->type;
	shell->redir->last_nodetype = syntax_tree->type;
	syntax_tree = syntax_tree->right;
	if (shell->redir->first_nodetype == NODE_REDIRECT_IN)
	{
		assign_file_multiple(syntax_tree->left, shell,
			shell->redir->first_nodetype);
		if (implement_redirection(shell) == -1)
			return (-1);
	}
	i++;
	while (i < shell->redir->redir_nbr)
	{
		check_node_type(syntax_tree, shell);
		i++;
		if (is_redirect_node(syntax_tree->right))
			syntax_tree = handle_redirect_node(syntax_tree, shell);
		else
			execute_multiple_redirection(syntax_tree, shell);
	}
	return (1);
}
