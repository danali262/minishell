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
	{
		cmd_path = concat_path(directory, cmd_alias);
	}
	else
		cmd_path = ft_strjoin(directory, cmd_alias);
	return (cmd_path);
}

static int	is_valid_path(char *cmd_location)
{
	struct stat buffer;

	int exist = stat(cmd_location, &buffer);
    if(exist == 0)
	{
		return (1);
	}
	return (0);
}

static char	**get_directories_list()
{
	int			j;
	char		*path_str;


	path_str = getenv("PATH");
	j = 0;
	while (path_str[j] != '/')
		j++;
	return (ft_split(path_str + j, ':'));
}

char	*locate_executable_path(t_treenode *simple_cmd_node)
{
	char 		**dir_list;
	char		*cmd_location;
	int			i;

    dir_list = get_directories_list();
	i = 0;
	cmd_location = NULL;
	while (dir_list[i] != NULL)
	{
		cmd_location = append_cmd_to_dir(dir_list[i], simple_cmd_node->data);
		if (is_valid_path(cmd_location))
		{
			// printf("file path: %s\n", cmd_location);
			break;
		}
		i++;
		cmd_location = NULL;
	}
	free_array_memory(dir_list);
	dir_list = NULL;
	return (cmd_location);
}

