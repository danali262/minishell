#include "redirection.h"
#include "../shell_utilities.h"

void	check_node_type(t_treenode *node, t_shell *shell)
{
	if (node->type == NODE_REDIRECT_IN)
		shell->redir->redirect_in = 1;
	if (node->type == NODE_REDIRECT_OUT)
		shell->redir->redirect_out = 1;
	if (node->type == NODE_APPEND)
		shell->redir->redirect_app = 1;
}

void	handle_redirect_node_execution(t_treenode *node, t_shell *shell)
{
	int	fd;

	if (shell->redir->last_nodetype == NODE_REDIRECT_OUT)
	{
		fd = open(node->left->data, O_WRONLY | O_CREAT | O_TRUNC,
				0666);
		close(fd);
	}
	if (shell->redir->last_nodetype == NODE_APPEND)
	{
		fd = open(node->left->data, O_WRONLY | O_CREAT,
				0666);
		close(fd);
	}
}
