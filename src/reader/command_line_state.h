#ifndef COMMAND_LINE_STATE_H
# define COMMAND_LINE_STATE_H

# include <stddef.h>
# include <limits.h>

# define BUF_SIZE 131071

# define PROMPT "minishell-2.5$ "

typedef struct s_line
{
	char	*buf;
	size_t	size;
}				t_line;

#endif
