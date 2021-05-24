#ifndef KEYS_H
# define KEYS_H

# include "../command_history/command_history.h"

// /*
// ** Terminal capabilities for keys:
// */
# define ARROW_UP 'A'
# define ARROW_DOWN 'B'

//  ANSI escape sequences, which extend the functions available with the control
// codes:
# define ESC '\x1b'
# define ENTER '\x0a'
# define BACKSPACE '\x7f' // or '\x08' ????
# define CTRL_C '\x03'
# define CTRL_D '\x04'

// typedef struct s_keycodes_map
// {
// 	char	keycode;
// 	int		(*action)(t_shell *shell);
// }				t_keycodes_map;

char	get_keycode(int fd, char *sequence);
void	handle_key_action(t_shell *shell, char keycode);

#endif
