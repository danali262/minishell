#include "executor.h"
#include "builtins/builtins.h"
#include "../signals/signals.h"
#include "../redirection/redirection.h"
#include "../shell_utilities.h"

#include "libft.h"

#include <unistd.h>
#include <sys/errno.h>
#include <signal.h>
#include <string.h>

/*
** WIFEXITED  valuates to nonzero if status was returned
** by a normally terminated child process.
*/

static t_treenode	*simple_cmd_redirection(t_treenode *simple_cmd_node, t_shell
	*shell)
{
	int	res;

	if (shell->redir->semi_nbr > 0 || shell->redir->pipes_nbr > 0)
	{
		shell->redir->redirect_in = 0;
		shell->redir->redirect_out = 0;
		shell->redir->redirect_app = 0;
		simple_redirection(simple_cmd_node, shell);
	}
	res = implement_redirection(shell);
	if (res == -1)
	{
		restore_stdio(shell);
		return (NULL);
	}
	if (shell->redir->redir_nbr > 0 && is_redirect_node(simple_cmd_node))
		simple_cmd_node = simple_cmd_node->left;
	return (simple_cmd_node);
}

void	wait_for_child(pid_t pid, t_shell *shell)
{
	int	wait_return;
	int	status;

	status = 0;
	wait_return = 0;
	wait_return = wait(&status);
	if (wait_return != pid)
		restore_stdio(shell);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
}

void	create_child_process(char **argv, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	check_fork_error(pid, shell);
	if (pid == 0)
		execute_system_function(argv, shell);
	else
		wait_for_child(pid, shell);
}

int	run_cmd_executable(t_treenode *simple_cmd_node, t_shell *shell)
{
	char		*executable_path;
	char		**argv;

	executable_path = NULL;
	if (simple_cmd_node != NULL && simple_cmd_node->data[0] != '\0')
		executable_path = locate_executable_path(simple_cmd_node, shell);
	if (executable_path != NULL)
	{
		argv = fill_args_list(simple_cmd_node, executable_path, shell);
		executable_path = NULL;
		if (shell->redir->pipes_nbr == 0)
			create_child_process(argv, shell);
		else
			execute_system_function(argv, shell);
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

	signal(SIGQUIT, quit_execution);
	simple_cmd_node = simple_cmd_redirection(simple_cmd_node, shell);
	if (simple_cmd_node == NULL)
		return (ERROR);
	simple_cmd_node->data = parse_argument_value(simple_cmd_node, shell);
	if (simple_cmd_node->data == NULL)
		return (ERROR);
	builtin_result = can_execute_builtin(simple_cmd_node, shell);
	if (builtin_result == ERROR)
		return (ERROR);
	else if (builtin_result == NOT_BUILTIN)
	{
		if (run_cmd_executable(simple_cmd_node, shell) == ERROR)
			return (ERROR);
	}
	if (shell->redir->semi_nbr > 0 || shell->redir->pipes_nbr > 0)
		restore_stdio(shell);
	return (SUCCESS);
}
