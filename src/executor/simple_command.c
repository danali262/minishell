#include "executor.h"

#include "builtins/builtins.h"

#include "libft.h"

#include <unistd.h>


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
		return (0);
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

int	run_cmd_executable(t_treenode *simple_cmd_node)
{
	extern char **environ;
	char 		*executable_path;
	char 		**argv;

	executable_path = NULL;
	if (simple_cmd_node != NULL)
	{
		executable_path = locate_executable_path(simple_cmd_node);
	}
	if (executable_path != NULL)
	{
		argv = fill_args_list(simple_cmd_node, executable_path);
		if (execve(argv[0], argv, environ) == -1)
		{
			free_array_memory(argv);
			ft_putstr_fd("execve error.\n", STDOUT_FILENO);
			return (0);
		}
		free_array_memory(argv);
		free(executable_path);
	}
	else
		printf("minishell: %s: command not found\n", simple_cmd_node->data);
	return (1);
}


int	create_child_process(t_treenode *simple_cmd_node)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error. Unable to create the child process.\n", STDOUT_FILENO);
		exit(0);
	}
	else if (pid == 0)
	{
		if (!run_cmd_executable(simple_cmd_node))
			exit(1);
		exit(0);
	}
	else
	{
		if (!WIFEXITED(status))
		{
			if (wait(&status) != pid)
				ft_putstr_fd("wait error.\n", STDOUT_FILENO);	
		}
		return (1);
	}
}

int	run_simple_command(t_treenode *simple_cmd_node)
{
	int	builtin_result;

	builtin_result = can_execute_builtin(simple_cmd_node);
	if (builtin_result == -1) //if any error happened, with e.g. memory allocation
	{
		printf("builtin error.s\n"); //remove
		return (0);
	}
	else if (builtin_result == 0) //if it's not a builtin command
	{
		if (!create_child_process(simple_cmd_node))
			return (0);
	}
	return (1);
}
