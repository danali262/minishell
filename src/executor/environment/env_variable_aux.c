#include "../executor.h"
#include "environment.h"

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

char	*create_substr_with_envar_value(t_arg_with_envvar *arg,
	t_shell *shell)
{
	size_t	envvar_len;
	char	*temp;
	char	*envvar_start;

	envvar_start = ft_strchr(arg->search_start, '$');
	envvar_len = 0;
	if (arg->search_start != envvar_start
		|| is_wrapped_in_single_quotes(arg->start, envvar_start)
		|| (*(envvar_start + 1) != '?'
			&& !is_allowed_in_envvar_name(*(envvar_start + 1))))
	{
		arg->offset = envvar_start - arg->search_start;
		if (is_wrapped_in_single_quotes(arg->start, envvar_start)
			|| (*(envvar_start + 1) != '?'
				&& !is_allowed_in_envvar_name(*(envvar_start + 1))))
			arg->offset++;
		temp = create_substring(arg->search_start, arg->offset);
	}
	else
	{
		temp = replace_name_with_value(arg->search_start, shell, &envvar_len);
		arg->offset = envvar_len;
	}
	return (temp);
}

static char	*add_envar_value_to_argument(t_arg_with_envvar *arg_with_envvar,
	char *new_arg_value, t_shell *shell)
{
	char	*temp;

	temp = create_substr_with_envar_value(arg_with_envvar, shell);
	if (temp != NULL)
	{
		new_arg_value = update_argument(new_arg_value, temp);
		free(temp);
		if (new_arg_value == NULL)
			return (NULL);
	}
	return (new_arg_value);
}

/*
**  Separate start and search_start are needed to keep track of single quotes and
**  several $ if they happen to be within one argument.
**	If there happen to be several environmemt variables inside the argument,
**  the string is divided into chunks when $ is found.
**  After the previous chunk is parsed the search start is moved.
*/

char	*create_new_argument_string(char *argument, t_shell *shell)
{
	t_arg_with_envvar	arg_with_envvar;
	char				*new_arg_value;

	arg_with_envvar.start = argument;
	arg_with_envvar.search_start = arg_with_envvar.start;
	new_arg_value = NULL;
	while (*arg_with_envvar.search_start != '\0')
	{
		if (!contains_char(arg_with_envvar.search_start, '$'))
			break ;
		new_arg_value = add_envar_value_to_argument(&arg_with_envvar,
				new_arg_value, shell);
		arg_with_envvar.search_start += arg_with_envvar.offset;
	}
	if (*arg_with_envvar.search_start != '\0')
	{
		new_arg_value = update_argument(new_arg_value,
				arg_with_envvar.search_start);
		if (new_arg_value == NULL)
			return (NULL);
	}
	free(argument);
	return (new_arg_value);
}
