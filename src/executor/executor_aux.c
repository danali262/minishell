#include "executor.h"
#include "../redirection/redirection.h"

#include "libft.h"

#include <sys/errno.h>
#include <stdlib.h>

char	*concat_path(char *left, char *right)
{
	char	*path;
	size_t	left_len;
	size_t	right_len;

	left_len = ft_strlen(left);
	right_len = ft_strlen(right);
	path = malloc(sizeof(char) * (left_len + right_len) + 2);
	if (!path)
	{
		printf("Error: unable to allocate memory for the path.\n");
		return (NULL);
	}
	ft_memmove(path, left, left_len);
	path[left_len] = '/';
	ft_memmove(path + left_len + 1, right, right_len);
	path[left_len + right_len + 1] = '\0';
	return (path);
}

char	*check_envars_and_quotes(t_treenode *arg_node, t_shell *shell)
{
	if (is_envar(arg_node->data))
	{
		arg_node->data = handle_argument_with_envvars(arg_node, shell);
		if (arg_node->data == NULL)
			return (NULL);
	}
	else
		arg_node->data = strip_quotes(arg_node->data);
	return (arg_node->data);
}

void	check_fork_error(pid_t pid, t_shell *shell)
{
	if (pid < 0)
	{
		restore_stdio(shell);
		printf("Error creating child process.\n\r");
		exit(errno);
	}
}

bool	is_command(char *str_to_compare, char *command)
{
	if (ft_strcmp(str_to_compare, command) == 0)
		return (true);
	return (false);
}

bool	is_preceeded_by_single_backslash(char *arg_string)
{
	char	*backslash_position;

	backslash_position = ft_strchr(arg_string, '\\');
	if (backslash_position == NULL)
		return (false);
	if (*(backslash_position + 1) == '$')
		return (true);
	return (false);
}
