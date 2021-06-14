#include "redirection.h"
#include "../executor/executor.h"

// static void	exec_child(int *file_desc, t_treenode *node, t_shell *shell)
// {
// 	int	pid;
// 	int status;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(file_desc[0], 0);
// 		close(file_desc[1]);
// 		close(file_desc[0]);
// 		run_simple_command(node->right, shell);	
// 	}
// 	else
// 	{
// 		// waitpid(pid, &status,0);
// 		dup2(file_desc[1], 1);
// 		close(file_desc[1]);
// 		close(file_desc[0]);
// 		run_simple_command(node->left, shell);
// 	}
// }


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
		// exec_child(file_desc, node, shell);
	else
	{
		dup2(file_desc[1], 1);
		close(file_desc[1]);
		close(file_desc[0]);
		run_simple_command(node->left, shell);
		waitpid(pid, &status, 0);
	}
}
