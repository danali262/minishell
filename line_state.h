#ifndef LINE_STATE_H
# define LINE_STATE_H

# include <stddef.h>
# include <limits.h>

# define BUF_SIZE ARG_MAX


typedef struct s_line_state
{
	char	*buf;
	size_t	line_len;
	size_t	history_index;
}				t_line_state;

#endif
