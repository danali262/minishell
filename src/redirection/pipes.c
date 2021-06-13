#include "redirection.h"
#include "../executor/executor.h"

void    handle_pipeline(t_treenode *node, t_shell *shell)
{
    int file_desc[2];
    int pid;
    int status;

	shell->redir->stdoutfd = dup(STDOUT_FILENO);
	shell->redir->stdinfd = dup(STDIN_FILENO);
	if (pipe(file_desc) != 0)
	{
		printf("Error creating pipe\n");
		exit(-1);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(file_desc[0], 0);
		close(file_desc[1]);
		close(file_desc[0]);
		run_simple_command(node->right, shell);	

	}
	else
	{
		dup2(file_desc[1], 1);
		close(file_desc[1]);
		close(file_desc[0]);
		run_simple_command(node->left, shell);
		waitpid(pid, &status, 0);
	}
}
