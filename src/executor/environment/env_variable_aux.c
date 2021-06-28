#include "../executor.h"

#include "libft.h"

char	*update_argument(char *new_arg_value, char *temp)
{
	char	*temp_arg_value;

	temp_arg_value = NULL;
	if (new_arg_value == NULL)
		temp_arg_value = ft_strdup(temp);
	else
		temp_arg_value = ft_strjoin(new_arg_value, temp);
	if (!temp_arg_value)
	{
		free(temp);
		free(new_arg_value);
		return (NULL);
	}
	free(new_arg_value);
	return (temp_arg_value);
}

char	*create_substring(char *start, size_t len)
{
	char	*temp;

	temp = NULL;
	if (len != 0)
		temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	ft_memmove(temp, start, len);
	temp[len] = '\0';
	return (temp);
}

/*
** environment variables cannot be non-alphanum except for $?
*/

char	*create_substr_with_envar_value(char *search_start, char *envvar_start,
		size_t	*offset, t_shell *shell)
{
	size_t	envvar_len;
	char	*temp;

	envvar_len = 0;
	temp = NULL;
	if (search_start != envvar_start
		|| (*(envvar_start + 1) != '?' && !ft_isalnum(*(envvar_start + 1))))
	{
		if (*(envvar_start + 1) != '?' && !ft_isalnum(*(envvar_start + 1)))
			*offset = envvar_start - search_start + 1;
		else
			*offset = envvar_start - search_start;
		temp = create_substring(search_start, *offset);
	}
	else
	{
		temp = replace_name_with_value(search_start, shell, &envvar_len);
		*offset = envvar_len;
	}
	return (temp);
}

static char	*concat_envar_value_to_argument(char *search_start,
	char *envvar_start, size_t *offset, t_shell *shell)
{
	char	*temp;
	char	*new_arg_value;

	new_arg_value = NULL;
	temp = create_substr_with_envar_value(search_start, envvar_start,
			offset, shell);
	if (temp != NULL)
	{
		new_arg_value = update_argument(new_arg_value, temp);
		free(temp);
		if (new_arg_value == NULL)
			return (NULL);
	}
	return (new_arg_value);
}

char	*create_new_argument_string(char *argument, t_shell *shell)
{
	char	*envvar_start;
	char	*search_start;
	char	*new_arg_value;
	size_t	offset;

	search_start = argument;
	while (*search_start != '\0')
	{
		envvar_start = ft_strchr(search_start, '$');
		if (envvar_start == NULL)
			break ;
		new_arg_value = concat_envar_value_to_argument(search_start,
				envvar_start, &offset, shell);
		search_start += offset;
	}
	if (*search_start != '\0')
	{
		new_arg_value = update_argument(new_arg_value, search_start);
		if (new_arg_value == NULL)
			return (NULL);
	}
	free(argument);
	return (new_arg_value);
}
