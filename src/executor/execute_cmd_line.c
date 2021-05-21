#include "executor.h"

#include "../parser/parser.h"

#include "libft.h"

#include <unistd.h>
#include <sys/wait.h>


void	execute_job(t_treenode *job_node, t_shell *shell)
{
	if (job_node == NULL)
		return ;
	// if (job_node->type == NODE_PIPE) // uncomment when pipeline is implemented
	// {
	// 	handle_pipeline(job_node);
	// }
	// else
		run_simple_command(job_node, shell);
}

void	execute_command_line(t_treenode *top_node, t_shell *shell)
{
	if (top_node == NULL)
		return ;
	if (top_node->type == NODE_SEMI || top_node->type == NODE_PIPE)
	{
		execute_job(top_node->left, shell);
		execute_command_line(top_node->right, shell);
	}
	else
		execute_job(top_node, shell);
}
