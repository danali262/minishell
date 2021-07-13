#include "executor.h"
#include "../redirection/pipes.h"
#include "../redirection/redirection.h"

#include "../parser/parser.h"

#include "libft.h"

#include <unistd.h>
#include <sys/wait.h>

void	run_executor(t_shell *shell)
{
	int	res;

	res = 1;
	if (shell->redir->semi_nbr == 0 && shell->redir->pipes_nbr == 0)
		res = check_for_redirection(shell->syntax_tree, shell);
	if (res == 1)
		execute_command_line(shell->syntax_tree, shell);
	if (shell->redir->semi_nbr == 0 && shell->redir->pipes_nbr == 0)
		restore_stdio(shell);
	delete_node(&shell->syntax_tree);
}

void	execute_command_line(t_treenode *top_node, t_shell *shell)
{
	if (top_node == NULL)
		return ;
	if (top_node->type == NODE_SEMI)
	{
		execute_job(top_node->left, shell);
		execute_command_line(top_node->right, shell);
	}
	else
		execute_job(top_node, shell);
}

void	execute_job(t_treenode *job_node, t_shell *shell)
{
	if (job_node == NULL)
		return ;
	if (job_node->type == NODE_PIPE)
		handle_pipeline(job_node, shell);
	else
	{
		shell->redir->pipes_nbr = 0;
		run_simple_command(job_node, shell);
	}
}
