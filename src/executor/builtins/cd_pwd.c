#include "builtins.h"
#include "../executor.h"

#include "libft.h"

#include <unistd.h>
#include <string.h>
#include <sys/errno.h>

/*
** bash doesn't care if there are any arguments after pwd,
** it ignores them and prints the current location
** we have also removed the check for too many arguments (like in zsh)
** or invalid option
** as our pwd is expected to work without options
*/

int	execute_pwd(t_treenode *simple_cmd_node, t_shell *shell)
{
	char	pwd_value[256];

	(void)simple_cmd_node;
	(void)shell;
	if (getcwd(pwd_value, sizeof(pwd_value)) == NULL)
		printf("pwd: %s\n\r", strerror(errno));
	printf("%s\n\r", pwd_value);
	return (SUCCESS);
}

static char	*change_directory(t_treenode *arg_node, t_shell *shell)
{
	char		*updated_cwd;
	char		pwd_value[256];

	updated_cwd = NULL;
	if (arg_node == NULL)
		updated_cwd = ft_strdup(getenv("HOME"));
	else
	{
		arg_node->data = check_envars_and_quotes(arg_node, shell);
		if (arg_node->data == NULL)
			return (NULL);
		if (arg_node->data[0] == '/')
			updated_cwd = ft_strdup(arg_node->data);
		else
		{
			updated_cwd = concat_path(getcwd(pwd_value, sizeof(pwd_value)),
					arg_node->data);
			if (updated_cwd == NULL)
				return (NULL);
		}
	}
	if (chdir(updated_cwd) != 0)
	{
		free(updated_cwd);
		return (NULL);
	}
	return (updated_cwd);
}

int	execute_cd(t_treenode *simple_cmd_node, t_shell *shell)
{
	char		*updated_cwd;

	updated_cwd = change_directory(simple_cmd_node->left, shell);
	if (updated_cwd == NULL)
	{
		printf("minishell: cd: %s: %s\n\r", simple_cmd_node->left->data,
			strerror(errno));
		return (ERROR);
	}
	else
	{
		if (change_env_value(shell, "PWD", updated_cwd) == ERROR)
		{
			printf("Error: unable to allocate memory.\n\r");
			free(updated_cwd);
			return (ERROR);
		}
	}
	free(updated_cwd);
	return (SUCCESS);
}
