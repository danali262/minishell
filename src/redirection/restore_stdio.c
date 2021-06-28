#include "redirection.h"

static void	restore_stdio_pipes(t_shell *shell)
{
	dup2(shell->redir->stdinfd, STDIN_FILENO);
	dup2(shell->redir->stdoutfd, STDOUT_FILENO);
}

void	restore_stdio(t_shell *shell)
{
	if (shell->redir->filename_in)
	{
		free(shell->redir->filename_in);
		shell->redir->filename_in = NULL;
	}
	if (shell->redir->filename_out != NULL)
	{
		free(shell->redir->filename_out);
		shell->redir->filename_out = NULL;
	}
	if (shell->redir->filename_app)
	{
		free(shell->redir->filename_app);
		shell->redir->filename_app = NULL;
	}
	if (shell->redir->redirect_in == 1)
		dup2(shell->redir->stdinfd, STDIN_FILENO);
	if (shell->redir->redirect_out == 1)
		dup2(shell->redir->stdoutfd, STDOUT_FILENO);
	if (shell->redir->redirect_app == 1)
		dup2(shell->redir->stdoutfd, STDOUT_FILENO);
	if (shell->redir->pipes_nbr > 0)
		restore_stdio_pipes(shell);
}
