#ifndef UPDATE_HISTORY_H
# define UPDATE_HISTORY_H

# include "command_history.h"
# include "line_state.h"

int	add_history_line(t_history *history, t_line *line_state);
int	show_prev_history(t_history *history, t_line *line_state);
int	show_next_history(t_history *history, t_line *line_state);

#endif
