#ifndef CURSOR_H
# define CURSOR_H

# include <stddef.h>

# define REQUEST_CUR_POS "\x1b[6n"

/*
** \033[6n DSR(device status report)-Request cursor position
*/

typedef struct s_cursor
{
	size_t	col;
	size_t	row;
}				t_cursor;

int get_cursor_pos(void);
#endif
