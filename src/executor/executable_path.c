#include "executor.h"

#include "builtins/builtins.h"

#include "libft.h"

#include <unistd.h>
#include<sys/stat.h>

static char	*append_cmd_to_dir(char *directory, char *cmd_alias)
{
	size_t	dir_len;
	size_t	alias_len;
	char	*cmd_path;

	dir_len = ft_strlen(directory);
	alias_len = ft_strlen(cmd_alias);
	if (directory[dir_len] != '/')
	{
		cmd_path = malloc(sizeof(char) * (dir_len + alias_len) + 2);
		ft_memmove(cmd_path, directory, dir_len);
		cmd_path[dir_len] = '/';
		ft_memmove(cmd_path + dir_len + 1, cmd_alias, alias_len);
		cmd_path[dir_len + alias_len + 2] = '\0';
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
	int			i;
	int			j;
	extern char **environ;
	char		*path_str;

	i = 0;
	while (environ[i] != 0)
	{
		if (ft_strncmp(environ[i], "PATH", 4) == 0)
            break ;
		i++;
	}
	path_str = environ[i];
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
	return (cmd_location);
}

