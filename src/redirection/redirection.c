#include "redirection.h"

void	restore_stdio(t_shell *shell)
{
	if (shell->redir->redirect_in == 1)
	{
		free(shell->redir->filename_in);
		dup2(shell->redir->stdinfd, STDIN_FILENO);
	}
	if (shell->redir->redirect_out == 1)
	{
		free(shell->redir->filename_out);
		dup2(shell->redir->stdoutfd, STDOUT_FILENO);
	}
	if (shell->redir->redirect_app)
	{
		free(shell->redir->filename_app);
			
	}
}

static void	assign_file(t_treenode *syntax_tree, t_shell *shell)
{
	if (shell->redir->redirect_in == 1)
		shell->redir->filename_in = ft_strdup(syntax_tree->data);
	else if (shell->redir->redirect_out == 1)
		shell->redir->filename_out = ft_strdup(syntax_tree->data);
	else
		shell->redir->filename_app = ft_strdup(syntax_tree->data);
}

void    check_for_redirection(t_treenode *syntax_tree, t_shell *shell)
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
		assign_file(syntax_tree, shell);
// 	// if (shell->redir->redirect_in == 1)
// 	// {
// 	// 	printf("REDIRECTION_IN is ON\n");
// 	// 	printf("input redirected from %s\n", shell->redir->filename_in);
// 	// }
// 	// if (shell->redir->redirect_out == 1)
// 	// {
// 	// 	printf("REDIRECTION_OUT is ON\n");
// 	// 	printf("output redirected to %s\n", shell->redir->filename_out);
// 	// }
// 	// if (shell->redir->redirect_app == 1)
// 	// {
// 	// 	printf("REDIRECTION_APPEND is ON\n");
// 	// 	printf("output appended to %s\n", shell->redir->filename_app);
// 	// }
	check_for_redirection(syntax_tree->left, shell);
	check_for_redirection(syntax_tree->right, shell);
}