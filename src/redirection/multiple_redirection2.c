#include "redirection.h"

static void	assign_file_in(t_treenode *syntax_tree, t_shell *shell)
{
	if (shell->redir->filename_in)
	{
		free(shell->redir->filename_in);
		shell->redir->filename_in = NULL;
	}
	shell->redir->filename_in = ft_strdup(syntax_tree->data);
}

static void	assign_file_out(t_treenode *syntax_tree, t_shell *shell)
{
	if (shell->redir->filename_out)
	{
		free(shell->redir->filename_out);
		shell->redir->filename_out = NULL;
	}
	shell->redir->filename_out = ft_strdup(syntax_tree->data);
}

static void	assign_file_app(t_treenode *syntax_tree, t_shell *shell)
{
	if (shell->redir->filename_app)
	{
		free(shell->redir->filename_app);
		shell->redir->filename_app = NULL;
	}
	shell->redir->filename_app = ft_strdup(syntax_tree->data);
}

void	assign_file_multiple(t_treenode *syntax_tree, t_shell *shell, int
		type)
{
	if (type == NODE_REDIRECT_IN)
		assign_file_in(syntax_tree, shell);
	else if (type == NODE_REDIRECT_OUT)
		assign_file_out(syntax_tree, shell);
	else
		assign_file_app(syntax_tree, shell);
}

void	handle_multiple_append(t_treenode *node, int saved_type, t_shell
	*shell)
{
	int	fd;

	assign_file_multiple(node->left, shell, saved_type);
	assign_file_multiple(node->right, shell, node->type);
	if (node->type == NODE_REDIRECT_OUT)
	{
		fd = open(shell->redir->filename_app, O_WRONLY | O_CREAT,
				0777);
		close(fd);
		shell->redir->redirect_app = 0;
	}
}
