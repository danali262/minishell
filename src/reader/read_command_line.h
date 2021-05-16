#ifndef READ_COMMAND_LINE_H
# define READ_COMMAND_LINE_H

#include "../command_history/command_history.h"
#include "../command_history/history_state.h"
#include "command_line_state.h"
#include "../shell_state.h"

# include <termios.h>

/*
** Set input mode with the termios struct:
*/
int		set_input_mode(struct termios *origin_attr);
int		reset_input_mode(struct termios *origin_attr, int error_code);

/*
** Command line:
*/

int		init_command_line(t_line *cmd_line);
void	clear_command_line(t_line *cmd_line);
void	free_command_line(t_line *cmd_line);
int		update_cmd_line(char *new_line, t_line *cmd_line);
void	erase_current_line(t_line *cmd_line);

int		read_input(t_shell *shell, struct termios *origin_attr);
int		read_command_line(int fd, t_shell *shell);
void	capture_keystrokes(int fd, char ch, t_shell *shell);


#endif
