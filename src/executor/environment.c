#include "executor.h"

void	create_env_var_list(char **env_list)
{
	extern char **environ;
    int			i;
    int			array_size;

	array_size = ft_calculate_array_size(environ);
    env_list = malloc(sizeof(char*) * array_size + 1);
    i = 0;
	while (i < array_size)
	{	
		env_list[i] = ft_strdup(environ[i]);
		i++;
	}
    env_list[i] = NULL;
}
