#include "redirection.h"

static int	implement_node_redirect_in(t_shell *shell)
{
	shell->redir->stdinfd = dup(STDIN_FILENO);
	shell->redir->fd = open(shell->redir->filename_in, O_RDONLY);
	if (shell->redir->fd < 0)
	{
		ft_putstr_fd("No such file or directory\n", STDOUT_FILENO);
		return (-1);
	}
	if (dup2(shell->redir->fd, STDIN_FILENO) < 0)
		redirection_error(shell, 1);
	close(shell->redir->fd);
	return (1);
}

static void	implement_node_redirect_out(t_shell *shell)
{
	shell->redir->stdoutfd = dup(STDOUT_FILENO);
	shell->redir->fd = open(shell->redir->filename_out, O_WRONLY | O_CREAT
			| O_TRUNC, 0666);
	if ((shell->redir->fd < 0) || (dup2(shell->redir->fd, STDOUT_FILENO)
			< 0))
		redirection_error(shell, 2);
	close(shell->redir->fd);
}

static void	implement_node_redirect_app(t_shell *shell)
{
	shell->redir->stdoutfd = dup(STDOUT_FILENO);
	shell->redir->fd = open(shell->redir->filename_app, O_WRONLY | O_CREAT
			| O_APPEND, 0666);
	if ((shell->redir->fd < 0) || (dup2(shell->redir->fd, STDOUT_FILENO)
			< 0))
		redirection_error(shell, 3);
	close(shell->redir->fd);
}

int	implement_redirection(t_treenode *node, t_shell *shell)
{
	int res;

	if (node->type == NODE_REDIRECT_IN)
	{
		res = implement_node_redirect_in(shell);
		return (res);
	}
	if (node->type == NODE_REDIRECT_OUT)
	{
		implement_node_redirect_out(shell);
		return (1);
	}
	if (node->type == NODE_APPEND)
	{
		implement_node_redirect_app(shell);
		return (1);
	}
	return (0);
}
