#include "executor.h"

#include "builtins/builtins.h"
#include "../signals/signals.h"
#include "../redirection/redirection.h"

#include "libft.h"

#include <unistd.h>
#include <sys/errno.h>
#include <signal.h>
#include <string.h>

char **fill_args_list(t_treenode *simple_cmd_node, char *executable_path, t_shell *shell)
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
		arg_node->data = check_envars_and_quotes(arg_node, shell);
		if (arg_node->data != NULL)
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

void	create_child_process(char **argv, t_shell *shell)
{
	pid_t 		pid;
	extern char	**environ;
	int 		status;

	pid = fork();
	if (pid < 0)
	{
		restore_stdio(shell);
		ft_putstr_fd("Error. Unable to create the child process.\n\r", STDOUT_FILENO);
		exit(errno);
	}
	else if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			printf("minishell: %s\n\r", strerror(errno));
			exit(126);
		}
	}
	else
	{
		int wait_return = wait(&status);
		if (wait_return != pid)
		{
			restore_stdio(shell);
			ft_putstr_fd("wait error\n\r", STDOUT_FILENO);	
		}
		if (WIFEXITED(status))
		{
			shell->exit_code = WEXITSTATUS(status);
			// printf("child exited\n\r"); //remove. for debug
			// printf("exit code: %d\n\r", shell->exit_code); //remove. for debug
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
		argv = fill_args_list(simple_cmd_node, executable_path, shell);
		create_child_process(argv, shell);
		free_array_memory(argv);
		argv = NULL;
	}
	else
	{
		restore_stdio(shell);
		printf("minishell: %s: command not found\n\r", simple_cmd_node->data);
		shell->exit_code = 127;
	}
	return (SUCCESS);
}

int	run_simple_command(t_treenode *simple_cmd_node, t_shell *shell)
{
	int		builtin_result;
	int		res;
	char	*command;

	signal(SIGQUIT, quit_execution);
	simple_cmd_node->data = strip_quotes(simple_cmd_node->data);
	res = implement_redirection(simple_cmd_node, shell);
	if (res == -1)
		return (ERROR);
	else if (res)
		simple_cmd_node = simple_cmd_node->left;
	if (is_envar(simple_cmd_node))
	{
		command = handle_argument_with_envvars(simple_cmd_node, shell);
		if (command != NULL)
			simple_cmd_node->data = command;
	}
	builtin_result = can_execute_builtin(simple_cmd_node, shell);
	if (builtin_result == ERROR)
		return (ERROR);
	else if (builtin_result == NOT_BUILTIN)
	{
		if (run_cmd_executable(simple_cmd_node, shell) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
