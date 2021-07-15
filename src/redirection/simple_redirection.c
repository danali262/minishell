#include "redirection.h"
#include "../executor/executor.h"

static void	assign_file_simple(t_treenode *syntax_tree, t_shell *shell)
{
	syntax_tree->data = strip_quotes(syntax_tree->data);
	if (shell->redir->redirect_in == 1)
		shell->redir->filename_in = ft_strdup(syntax_tree->data);
	else if (shell->redir->redirect_out == 1)
		shell->redir->filename_out = ft_strdup(syntax_tree->data);
	else
		shell->redir->filename_app = ft_strdup(syntax_tree->data);
}

static void	redirect_rhombus(t_treenode *syntax_tree)
{
	char	*filename;
	int		fd;

	filename = ft_strdup(syntax_tree->right->data);
	fd = open(filename, O_WRONLY | O_CREAT, 0666);
	close(fd);
	free(filename);
}

void	simple_redirection(t_treenode *syntax_tree, t_shell *shell)
{
	if (!syntax_tree)
		return ;
	if (syntax_tree->type == NODE_RHOMBUS)
	{
		redirect_rhombus(syntax_tree);
		return ;
	}
	if (syntax_tree->type == NODE_REDIRECT_IN)
		shell->redir->redirect_in = 1;
	if (syntax_tree->type == NODE_REDIRECT_OUT)
		shell->redir->redirect_out = 1;
	if (syntax_tree->type == NODE_APPEND)
		shell->redir->redirect_app = 1;
	if (syntax_tree->type == NODE_FILE)
		assign_file_simple(syntax_tree, shell);
	simple_redirection(syntax_tree->left, shell);
	simple_redirection(syntax_tree->right, shell);
}

int	check_for_redirection(t_treenode *syntax_tree, t_shell *shell)
{
	int	res;

	res = 1;
	if (shell->redir->redir_nbr == 0)
		return (res);
	else if (shell->redir->redir_nbr == 1)
		simple_redirection(syntax_tree, shell);
	else
		res = multiple_redirection(syntax_tree, shell);
	return (res);
}
