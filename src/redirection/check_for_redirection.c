#include "redirection.h"

void	restore_stdio(t_shell *shell)
{
	if (shell->redir->redirect_in == 1)
	{
		if (shell->redir->filename_in)
		{
			free(shell->redir->filename_in);
			shell->redir->filename_in = NULL;
		}
		dup2(shell->redir->stdinfd, STDIN_FILENO);
	}
	if (shell->redir->redirect_out == 1)
	{
		if (shell->redir->filename_out != NULL)
		{
			free(shell->redir->filename_out);
			shell->redir->filename_out = NULL;
		}
		dup2(shell->redir->stdoutfd, STDOUT_FILENO);
	}
	if (shell->redir->redirect_app == 1)
	{
		if (shell->redir->filename_app)
		{
			free(shell->redir->filename_app);
			shell->redir->filename_app = NULL;
		}
		dup2(shell->redir->stdoutfd, STDOUT_FILENO);
	}
	if (shell->redir->pipes_nbr  > 0)
	{
		dup2(shell->redir->stdinfd, STDIN_FILENO);
		dup2(shell->redir->stdoutfd, STDOUT_FILENO);
	}
}

static void	assign_file_simple(t_treenode *syntax_tree, t_shell *shell)
{
	if (shell->redir->redirect_in == 1)
		shell->redir->filename_in = ft_strdup(syntax_tree->data);
	else if (shell->redir->redirect_out == 1)
		shell->redir->filename_out = ft_strdup(syntax_tree->data);
	else
		shell->redir->filename_app = ft_strdup(syntax_tree->data);
}

static void	simple_redirection(t_treenode *syntax_tree, t_shell *shell)
{
	if (!syntax_tree)
		return ;
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

static void	assign_file_multiple(t_treenode *syntax_tree, t_shell *shell, int type)
{
	if (type == NODE_REDIRECT_IN)
		shell->redir->filename_in = ft_strdup(syntax_tree->data);
	else if (type == NODE_REDIRECT_OUT)
		shell->redir->filename_out = ft_strdup(syntax_tree->data);
	else
		shell->redir->filename_app = ft_strdup(syntax_tree->data);
}

static void	multiple_redirection(t_treenode *syntax_tree, t_shell *shell)
{
	int	i;
	int	saved_type;

	i = 0;
	if (syntax_tree->type == NODE_REDIRECT_IN)
		shell->redir->redirect_in = 1;
	if (syntax_tree->type == NODE_REDIRECT_OUT)
		shell->redir->redirect_out = 1;
	if (syntax_tree->type == NODE_APPEND)
		shell->redir->redirect_app = 1;
	saved_type = syntax_tree->type;
	syntax_tree = syntax_tree->right;
	i++;
	while (i < shell->redir->redir_nbr)
	{
		if (syntax_tree->type == NODE_REDIRECT_IN)
			shell->redir->redirect_in = 1;
		if (syntax_tree->type == NODE_REDIRECT_OUT)
			shell->redir->redirect_out = 1;
		if (syntax_tree->type == NODE_APPEND)
			shell->redir->redirect_app = 1;
		i++;
		if (syntax_tree->right->type == NODE_REDIRECT_IN || syntax_tree->right->type == NODE_REDIRECT_OUT || syntax_tree->right->type == NODE_APPEND)
		{
			syntax_tree = syntax_tree->right;
			continue;
		}
		else
		{
			assign_file_multiple(syntax_tree->left, shell, saved_type);
			assign_file_multiple(syntax_tree->right, shell, syntax_tree->type);
		}
	}
}

void	check_for_redirection(t_treenode *syntax_tree, t_shell *shell)
{
	if (shell->redir->redir_nbr == 0)
		return ;
	else if (shell->redir->redir_nbr == 1)
		simple_redirection(syntax_tree, shell);
	else
		multiple_redirection(syntax_tree, shell);
}
