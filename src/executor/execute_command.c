#include "executor.h"

#include "parser/parser.h"
#include "builtins/builtins.h"

#include "libft.h"

#include <unistd.h>
#include <sys/wait.h>

int	find_path_and_exec(t_treenode *syntax_tree)
{
	extern char **environ;

	char    *argv[2]; //it's hardcoded now, will need to add the functionality looking for the PATH
    argv[0] = "/bin/ls";
	argv[1] = NULL; //assigning flags and other args to the array

	if (syntax_tree != NULL)
	{
		// condition needed for compilation only
	}
		// if (PATH / command is found)
		// {
		int returnval = execve(argv[0], argv, environ);
		if (returnval == -1)
		{
			ft_putstr_fd("execve error.\n", STDOUT_FILENO);
			return (0);
		}
		printf("executed\n"); //remove
		// }
		// else
		// printf("bash: %s: command not found\n", syntax_tree->left);
	return (1);
}

int	run_simple_command(t_treenode *cmd_node)
{
	int	builtin_result;

	builtin_result = can_execute_builtin(cmd_node);
	if (builtin_result == -1) //if any error happened, with e.g. memory allocation
	{
		printf("builtin error.s\n"); //remove
		return (0);
	}
	else if (builtin_result == 0) //if it's not a builtin command
	{
		find_path_and_exec(cmd_node);
	}
	return (1);
}

void	execute_job(t_treenode *job_node)
{
	if (job_node == NULL)
		return ;
	// if (job_node->type == NODE_PIPE) // uncomment when pipeline is implemented
	// {
	// 	handle_pipeline(job_node);
	// }
	// else
		run_simple_command(job_node);
}

void	execute_command_line(t_treenode *top_node)
{
	if (top_node == NULL)
		return ;
	if (top_node->type == NODE_SEMI || top_node->type == NODE_PIPE)
	{
		execute_job(top_node->left);
		execute_command_line(top_node->right);
	}
	else
		execute_job(top_node);
}




// 
// int	run_child_process(t_treenode *syntax_tree)
// {
// 	if (syntax_tree->type == NODE_PATH) // or if semicolomn or pipe without another command after them
// 	{
// 		if (!run_simple_command(syntax_tree))
// 			return (0);
// 		return (1);
// 	}
// 	else 
// 	{
// 		while (syntax_tree->left != NULL)
// 		{
// 			if (syntax_tree->type == NODE_SEMI)
// 			{
// 				if (!run_simple_command(syntax_tree))
// 					return (0);
// 			}
// 			// here pipe and redirection types are added
// 		}
// 	}
// 	return (1);
// }
// 
// int	create_child_process(t_treenode *syntax_tree)
// {
// 	pid_t pid;
// 	int status;
// 
// 	//creating a child process:
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		ft_putstr_fd("Error. Unable to create the child process.\n", STDOUT_FILENO);
// 		exit(0);
// 	}
// 	else if (pid == 0)
// 	{
// 		if (!run_child_process(syntax_tree))
// 			exit(1);
// 		exit(0);
// 	}
// 	else
// 	{
// 		if (!WIFEXITED(status))
// 		{
// 			if (wait(&status) != pid)
// 				ft_putstr_fd("Wait error.\n", STDOUT_FILENO);	
// 		}
// 		return (1);
// 	}
// }

