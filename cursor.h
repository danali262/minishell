#ifndef CURSOR_H
# define CURSOR_H

# include <stddef.h>

//  ANSI escape sequences, which extend the functions available with the control
// codes:
# define ESC '\033'
# define REQUEST_CUR_POS "\033[6n"
/*
** \033[6n DSR(device status report)-Request cursor position
*/

typedef struct s_cursor
{
	size_t	col;
	size_t	row;
}				t_cursor;

int get_cursor_pos();
#endif
