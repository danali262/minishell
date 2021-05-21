#include "executor.h"

#include "libft.h"

#include <stdlib.h>

int	create_env_var_list(t_shell *shell)
{
	extern char **environ;
    int			i;
    int			array_size;

	array_size = ft_calculate_array_size(environ);
	shell->env_list = malloc(sizeof(char*) * array_size + 1);
	if ((shell->env_list) == NULL)
		return (ERROR);
		i = 0;
	while (i < array_size)
	{	
		shell->env_list[i] = ft_strdup(environ[i]);
		i++;
	}
	shell->env_list[i] = NULL;
	return (SUCCESS);
}

int	change_env_value(t_shell *shell, char *var_name, char *new_value)
{
	int		i;
	size_t	var_name_len;
	size_t	new_value_len;
	char	*updated_envar;

	updated_envar = NULL;
	var_name_len = ft_strlen(var_name);
	new_value_len = ft_strlen(new_value);
	updated_envar = malloc(sizeof(char) * new_value_len + var_name_len + 2);
	if (!updated_envar)
		return (0);
	ft_memmove(updated_envar, var_name, var_name_len);
	updated_envar[var_name_len]= '=';
	ft_memmove(updated_envar + var_name_len + 1, new_value, new_value_len);
	i = 0;
	while (shell->env_list[i] != NULL)
	{
		if (ft_strncmp(shell->env_list[i], var_name, ft_strlen(var_name)) == 0)
			break ;
		i++;
	}
	free(shell->env_list[i]);
	shell->env_list[i] = updated_envar;
		return (1);
}
