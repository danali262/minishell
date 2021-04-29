#ifndef KEYS_H
# define KEYS_H

# include "command_history.h"
# include "line_state.h"

/*
** Terminal capabilities for keys:
*/
# define ARROW_UP 'A'
# define ARROW_DOWN 'B'

//  ANSI escape sequences, which extend the functions available with the control
// codes:
# define ESC '\x1b'
# define NEWLINE '\x0a'
# define CARRIAGE_RETURN '\x0d'
# define BACKSPACE '\x7f' // or '\x08' ????
# define CTRL_D '\x04'

typedef struct s_keycodes_map
{
	char	keycode;
	int		(*action)(t_history *history, t_line *line_state);
}				t_keycodes_map;

char	get_keycode(int fd, char *sequence);
void	map_key_actions(t_history *history, t_line *line_state, char keycode);

#endif
