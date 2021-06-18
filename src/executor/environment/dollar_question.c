#include "../executor.h"

#include "libft.h"

char	*replace_dollar_question(t_shell *shell)
{
	char	*value;
	char	*exit_code_str;

	value = NULL;
	exit_code_str = ft_itoa(shell->exit_code);
	value = exit_code_str;
	return (value);
}
