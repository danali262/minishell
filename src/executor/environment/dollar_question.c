#include "../executor.h"

#include "libft.h"

char	*replace_dollar_question(char *envvar, t_shell *shell, bool is_in_str)
{
	char	*value;
	char	*exit_code_str;
	size_t	data_len;

	value = NULL;
	data_len = 2;
	exit_code_str = ft_itoa(shell->exit_code);
	if (is_in_str == false)
		data_len = ft_strlen(envvar);
	if (data_len == 2)
		value = exit_code_str;
	else
	{
		value = ft_strjoin(exit_code_str, envvar + 2);
		free(exit_code_str);
	}
	return (value);
}
