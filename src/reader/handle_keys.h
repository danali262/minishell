#ifndef HANDLE_KEYS_H
# define HANDLE_KEYS_H

# include "../command_history/history_state.h"

# include "command_line_state.h"

int	handle_newline(t_history *history, t_line *cmd_line);
int	handle_backspace(t_history *history, t_line *cmd_line);
int	handle_eot(t_history *history, t_line *cmd_line);


#endif
