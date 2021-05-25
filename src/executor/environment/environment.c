#include "../executor.h"

#include "libft.h"

#include <stdlib.h>

// int	create_env_var_list(t_shell *shell)
// {
// 	extern char **environ;
//     int			i;
//     int			array_size;

// 	array_size = ft_calculate_array_size(environ);
// 	shell->env_list = malloc(sizeof(char*) * array_size + 1);
// 	if ((shell->env_list) == NULL)
// 		return (ERROR);
// 		i = 0;
// 	while (i < array_size)
// 	{	
// 		shell->env_list[i] = ft_strdup(environ[i]);
// 		i++;
// 	}
// 	shell->env_list[i] = NULL;
// 	return (SUCCESS);
// }

int	create_env_var_list(t_shell *shell)
{
	extern char **environ;
    t_list		*env_list;
	t_list		*envar_node;
	char		*envar_str;
	int			i;


	env_list = NULL;
	envar_node = NULL;
	envar_str = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		envar_str = ft_strdup(environ[i]);
		if (!envar_str)
			return (ERROR);
		envar_node = ft_lstnew(envar_str);
		if (!envar_node)
			return (ERROR);
		ft_lstadd_back(&env_list, envar_node);
		i++;
	}
// env_list printing function:

	// 	t_list *node = env_list; 
	// while (node->next != NULL)
	// {
	// 	printf("%s\n", node->content);
	// 	node = node->next;
	// }
	
	shell->env_list = env_list;
	return (SUCCESS);
}

int	change_env_value(t_shell *shell, char *var_name, char *new_value)
{
	int		i;
	size_t	var_name_len;
	size_t	new_value_len;
	char	*updated_envar;
	t_list	*envar_node;

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
	envar_node = shell->env_list;
	while (envar_node->next != NULL)
	{
		if (ft_strncmp(shell->env_list->content, var_name, ft_strlen(var_name)) == 0)
			break ;
		envar_node = envar_node->next;
	}
	free(envar_node->content);
	envar_node->content = updated_envar;
		return (1);
}
