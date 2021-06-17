#include "executor.h"
#include "../redirection/redirection.h"

#include <sys/errno.h>
#include <string.h>

void	execute_system_function(char **argv, t_shell *shell)
{
	extern char	**environ;

	if (execve(argv[0], argv, environ) == -1)
	{
		restore_stdio(shell);
		printf("minishell: %s\n\r", strerror(errno));
		shell->exit_code = 126;
	}
}

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
