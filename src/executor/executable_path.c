#include "executor.h"

#include "builtins/builtins.h"

#include "libft.h"

#include <unistd.h>
#include<sys/stat.h>
#include <stdlib.h>

static char	*append_cmd_to_dir(char *directory, char *cmd_alias)
{
	size_t	dir_len;
	char	*cmd_path;

	dir_len = ft_strlen(directory);
	if (directory[dir_len] != '/')
		cmd_path = concat_path(directory, cmd_alias);
	else
		cmd_path = ft_strjoin(directory, cmd_alias);
	if (cmd_path == NULL)
		return (NULL);
	return (cmd_path);
}

/*
** stat() retrieves information about the file, in the buffer
**     pointed to by buffer 
*/

static int	is_valid_path(char *cmd_location)
{
	struct stat	buffer;

	if (stat(cmd_location, &buffer) == 0)
		return (1);
	return (0);
}

static char	**get_directories_list(t_shell *shell)
{
	int		j;
	char	*path_str;
	char	**dir_list;

	path_str = get_envar_value("PATH", shell);
	if (path_str == NULL)
		return (NULL);
	j = 0;
	while (path_str[j] != '/')
		j++;
	dir_list = ft_split(path_str + j, ':');
	free(path_str);
	return (dir_list);
}

char	*locate_executable_path(t_treenode *simple_cmd_node, t_shell *shell)
{
	char	**dir_list;
	char	*cmd_location;
	int		i;

	if (is_valid_path(simple_cmd_node->data))
		return (ft_strdup(simple_cmd_node->data));
	dir_list = get_directories_list(shell);
	if (dir_list == NULL)
		return (NULL);
	i = 0;
	cmd_location = NULL;
	while (dir_list[i] != NULL)
	{
		cmd_location = append_cmd_to_dir(dir_list[i], simple_cmd_node->data);
		if (cmd_location == NULL)
			return (NULL);
		if (is_valid_path(cmd_location))
			break ;
		i++;
		free(cmd_location);
		cmd_location = NULL;
	}
	free_array_memory(dir_list);
	dir_list = NULL;
	return (cmd_location);
}
