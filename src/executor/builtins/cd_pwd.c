#include "builtins.h"
#include "../executor.h"

#include "libft.h"

#include <unistd.h>
#include <string.h>
#include <sys/errno.h>

/*
** bash doesn't care if there are any arguments after pwd, it ignres them and prints the current location
** we have also removed the check for too many arguments (like in zsh) or invalid option
** as our pwd is expected to work without options
*/

int	execute_pwd(t_treenode *simple_cmd_node, t_shell *shell)
{
	char	pwd_value[256];

	if (shell->env_list != NULL) // will need shell-> later on in pipes
	{
		
	}
	if (simple_cmd_node) // need to think of what to do with this parameter
	{
		
	}
	if (getcwd(pwd_value, sizeof(pwd_value)) == NULL)
		printf("pwd: %s\n\r", strerror(errno));
	printf("%s\n\r", pwd_value);
		return (SUCCESS);
}

char 	*change_directory(t_treenode *simple_cmd_node, int *cd_result)
{
	t_treenode	*arg_node;
	char		*updated_cwd;
	char		pwd_value[256];

	arg_node = simple_cmd_node->left;
	updated_cwd = NULL;
	if (arg_node->data[0] == '/')
	{
		updated_cwd = arg_node->data;
		*cd_result = chdir(updated_cwd);
	}
	else
	{
		updated_cwd = concat_path(getcwd(pwd_value, sizeof(pwd_value)),
				arg_node->data);
		if (updated_cwd == NULL)
			return (NULL);
		*cd_result = chdir(updated_cwd);
	}
	return (updated_cwd);
}

int	execute_cd(t_treenode *simple_cmd_node, t_shell *shell)
{
	int			cd_result;
	char		*updated_cwd;

	cd_result = -1;
	updated_cwd = NULL;
	if (simple_cmd_node->left == NULL)
	{
		updated_cwd = getenv("HOME");
		cd_result = chdir(updated_cwd);
	}
	else
		updated_cwd = change_directory(simple_cmd_node, &cd_result);
	if (cd_result != 0)
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
		return (SUCCESS);
}
