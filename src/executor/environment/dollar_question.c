#include "../executor.h"

#include "libft.h"

char	*replace_dollar_question(t_shell *shell)
{
	char	*exit_code_str;

	exit_code_str = ft_itoa(shell->exit_code);
	return (exit_code_str);
}
