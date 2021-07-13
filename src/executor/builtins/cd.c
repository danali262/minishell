#include "builtins.h"
#include "../executor.h"

#include "libft.h"

#include <unistd.h>
#include <string.h>
#include <sys/errno.h>

static char	*get_path_to_new_working_directory(char	*path)
{
	char		*updated_path;
	char		pwd_value[256];

	updated_path = NULL;
	if (path[0] == '/')
		updated_path = ft_strdup(path);
	else
	{
		updated_path = concat_path(getcwd(pwd_value, sizeof(pwd_value)),
				path);
		if (updated_path == NULL)
			return (NULL);
	}
	return (updated_path);
}

static char	*change_to_oldpwd(t_shell *shell)
{
	char		*updated_cwd;

	updated_cwd = get_envar_value("OLDPWD", shell);
	if (updated_cwd == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (NULL);
	}
	printf("%s\n", updated_cwd);
	return (updated_cwd);
}

static char	*append_tilde_value(char	*path)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(path + 2);
	free(path);
	path = concat_path(getenv("HOME"), temp);
	free(temp);
	return (path);
}

static char	*change_directory(t_treenode *arg_node, t_shell *shell)
{
	char	*updated_cwd;

	updated_cwd = NULL;
	if (arg_node == NULL || is_command("~", arg_node->data))
		updated_cwd = ft_strdup(getenv("HOME"));
	else if (is_command("-", arg_node->data))
		updated_cwd = change_to_oldpwd(shell);
	else
	{
		arg_node->data = parse_argument_value(arg_node, shell);
		if (arg_node->data == NULL)
			return (NULL);
		if (ft_strncmp("~/", arg_node->data, 2) == 0)
			arg_node->data = append_tilde_value(arg_node->data);
		updated_cwd = get_path_to_new_working_directory(arg_node->data);
		if (updated_cwd == NULL)
			return (NULL);
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
		if (!is_command("-", simple_cmd_node->left->data))
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
