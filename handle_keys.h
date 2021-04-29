#ifndef HANDLE_KEYS_H
# define HANDLE_KEYS_H

# include "command_history.h"
# include "line_state.h"

int	handle_newline(t_history *history, t_line *line_state);
int	handle_backspace(t_history *history, t_line *line_state);
int	handle_eot(t_history *history, t_line *line_state);


#endif
