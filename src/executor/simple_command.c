#include "executor.h"

#include "builtins/builtins.h"

#include "libft.h"

#include <unistd.h>
#include <sys/errno.h>

char **fill_args_list(t_treenode *simple_cmd_node, char *executable_path)
{
	t_treenode	*arg_node;
	int			arg_counter;
	char 		**arguments;

	arg_node = simple_cmd_node->left;
	arg_counter = 1;
	while (arg_node != NULL)
	{
		arg_counter++;
		arg_node = arg_node->left;
	}
	arguments = malloc(sizeof(char*) * arg_counter + 1);
	if (arguments == NULL)
		return (NULL);
	arguments[0] = executable_path;
	int i = 1;
	arg_node = simple_cmd_node->left;
	while (arg_node != NULL)
	{
		arguments[i] = ft_strdup(arg_node->data);
		i++;
		arg_node = arg_node->left;
	}
	arguments[arg_counter] = NULL;
	return (arguments);
}

/*
** WIFEXITED  valuates to nonzero if status was returned by a normally terminated child process. 
*/

void	create_child_process(char **argv)
{
	pid_t 		pid;
	extern char	**environ;
	int 		status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error. Unable to create the child process.\n", STDOUT_FILENO);
		exit(errno);
	}
	else if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			ft_putstr_fd("execve error.\n", STDOUT_FILENO);
			exit(126);
		}
	}
	else
	{
		int wait_return = wait(&status);
		// printf("wait_return: %d\n", wait_return);
		// printf("pid of the parent process: %d\n", pid);
		if (wait_return != pid)
			ft_putstr_fd("wait error\n", STDOUT_FILENO);	
		if (WIFEXITED(status) > 0)
		{
			printf("child exited\n"); //remove. for debug
		}
	}
}

int	run_cmd_executable(t_treenode *simple_cmd_node, t_shell *shell)
{
	char	*executable_path;
	char	**argv;

	executable_path = NULL;
	if (simple_cmd_node != NULL)
		executable_path = locate_executable_path(simple_cmd_node);
	if (executable_path != NULL)
	{
		argv = fill_args_list(simple_cmd_node, executable_path);
		// int i = 0;
		// while (argv[i] != NULL)//remove the printing array function!!!!!
		// {
		// 	printf("%s\n", argv[i]);
		// 	i++;
		// }
		// 	printf("%s\n", argv[i]);
		create_child_process(argv);
		free_array_memory(argv);
		argv = NULL;
	}
	else
	{
		printf("minishell: %s: command not found\n", simple_cmd_node->data);
		shell->exit_code = 127;
	}
	return (1);
}


int	run_simple_command(t_treenode *simple_cmd_node, t_shell *shell)
{
	int	builtin_result;

	builtin_result = can_execute_builtin(simple_cmd_node, shell);
	if (builtin_result == -1) //if any error happened, with e.g. memory allocation/ can it actually happen?
	{
		printf("builtin error\n"); //remove, set error code
		return (0);
	}
	else if (builtin_result == 0) //if it's not a builtin command
	{
		// if (!create_child_process(simple_cmd_node))
		if (!run_cmd_executable(simple_cmd_node, shell))
			return (0);
	}
	return (1);
}
