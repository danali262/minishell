#ifndef READ_COMMAND_LINE_H
# define READ_COMMAND_LINE_H

# include "../command_history/command_history.h"
# include "../command_history/history_state.h"
# include "command_line_state.h"
# include "../shell_state.h"

/*
**  ANSI escape sequences, which extend the functions available with the control
** codes:
*/
# define ESC '\x1b'
# define ENTER '\x0a'
# define CARRIAGE_RETURN '\x0d'
# define BACKSPACE '\x7f'
# define CTRL_C '\x03'
# define CTRL_D '\x04'

void	write_prompt(void);

/*
** Set input mode with the termios struct:
*/
int		set_input_mode(t_shell *shell);
int		reset_input_mode(t_shell *shell, int error_code);

/*
** Command line:
*/

int		init_command_line(t_line *cmd_line);
void	clear_command_line(t_line *cmd_line);
void	free_command_line(t_line *cmd_line);
int		update_cmd_line(char *new_line, t_line *cmd_line);
void	erase_current_line(t_line *cmd_line);

int		read_input(t_shell *shell);
int		read_command_line(int fd, t_shell *shell);
void	capture_keystrokes(int fd, char ch, t_shell *shell);

/*
** Handle keys:
*/
char	get_keycode(int fd, char *sequence);
void	handle_key_action(t_shell *shell, char keycode);

int		handle_enter(t_shell *shell);
void	handle_backspace(t_line *cmd_line);
int		handle_eot(t_shell *shell);
void	handle_interrupt(t_shell *shell);

#endif
