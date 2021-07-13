#ifndef COMMAND_LINE_STATE_H
# define COMMAND_LINE_STATE_H

# include <stddef.h>
# include <limits.h>

# define BUF_SIZE ARG_MAX

# define PROMPT "minishell-2.3$ "

typedef struct s_line
{
	char	*buf;
	size_t	size;
}				t_line;

#endif
