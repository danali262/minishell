#include "../executor.h"

#include "libft.h"

int	is_envar(t_treenode *arg_node)
{
	if (ft_strchr(arg_node->data, '$') == NULL)
		return (false);
	return (true);
}


char 	*update_argument(char *new_arg_value, char *temp)
{
	char	*temp_arg_value;

	temp_arg_value = NULL;
	if (new_arg_value == NULL)
		temp_arg_value = ft_strdup(temp);
	else
		temp_arg_value = ft_strjoin(new_arg_value, temp);
	if (!temp_arg_value)
		return (NULL);
	free(new_arg_value);
	return (temp_arg_value);
}

char	*create_substring(char *start, size_t len)
{
	char	*temp;

	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	ft_memmove(temp, start, len);
	temp[len] = '\0';
	return (temp);
}

char	*create_new_argument_string(char *search_start, t_shell *shell)
{
	char	*envvar_start;
	char	*new_arg_value;
	char	*temp;
	size_t  envvar_len;
    size_t  offset;

	envvar_start = NULL;
	new_arg_value = NULL;
    envvar_len = 0;
	while (*search_start != '\0')
	{
		temp = NULL;
		envvar_start = ft_strchr(search_start, '$');
		if (envvar_start == NULL)
			break ;
		if (search_start != envvar_start)
		{
			temp = create_substring(search_start, envvar_start - search_start);
			offset = ft_strlen(temp);
		}
		else
		{
			temp = replace_name_with_value(search_start, shell, &envvar_len, true);
			offset = envvar_len;
		}
        if (temp != NULL)
            new_arg_value = update_argument(new_arg_value, temp);
		search_start += offset;
        free(temp);
	}
		temp = create_substring(search_start, ft_strlen(search_start));
		new_arg_value = update_argument(new_arg_value, temp);
	return (new_arg_value);
}

