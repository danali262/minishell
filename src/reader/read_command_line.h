#ifndef READ_COMMAND_LINE_H
# define READ_COMMAND_LINE_H

#include "command_history/command_history.h"
#include "command_line_state.h"

#include <termios.h>

/*
** Set input mode with the termios struct:
*/
int	set_input_mode(struct termios *origin_attr);
int	reset_input_mode(struct termios *origin_attr, int error_code);

/*
** Command line:
*/

int	init_command_line(t_line *line_state);
int	clear_command_line(t_line *line_state);
void	free_command_line(t_line *line_state);

int	read_input(void);
int	read_command_line(int fd, t_history *history, t_line *line_state);




#endif
