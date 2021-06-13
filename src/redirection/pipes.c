#include "redirection.h"
#include "../executor/executor.h"

void    handle_pipeline(t_treenode *node, t_shell *shell)
{
    int file_desc[2];
    int pid;
    int status;

	shell->redir->stdinfd = dup(STDIN_FILENO);
	shell->redir->stdoutfd = dup(STDOUT_FILENO);
    shell->redir->pipe = 1;
    if (pipe(file_desc) != 0)
    {
        printf("Error creating the pipe.\n");
        exit(-1);
    }
    shell->redir->pipe_read = file_desc[0]; 
    shell->redir->pipe_write = file_desc[1];
    pid = fork();
    if (pid == -1)
    {
        printf("Error creating the child.\n");
        exit(-1);
    }
    else if (pid == 0)
    {
        if (node->right->type == NODE_PIPE)
            handle_pipeline(node->right, shell);
        // printf("I am in child2 PID : %d\n", getpid());
        dup2(shell->redir->pipe_read, 0);
        close(shell->redir->pipe_write);
        // close(shell->redir->pipe_read);
        // shell->redir->stdout_pipe = 0;
        if (node->right->type != NODE_PIPE)
            run_simple_command(node->right, shell);
    }
    else
    {
		waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        else
            printf("Child terminated abnormally. Code : %d\n", WEXITSTATUS(status));
        // printf("I am in parent2 PID : %d\n", getpid());
        dup2(shell->redir->pipe_write, 1);
        close(shell->redir->pipe_read);
        // close(shell->redir->pipe_write);
        // shell->redir->stdout_pipe = 1;
        if (node->left->type != NODE_PIPE)
            run_simple_command(node->left, shell);
    }
}
