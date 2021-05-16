#ifndef COMMAND_HISTORY_H
# define COMMAND_HISTORY_H

# include "history_state.h"
# include "../reader/command_line_state.h"
# include "../reader/read_command_line.h"

void	init_history(t_history *history);
void	free_history(t_history *history);
void	clear_history(t_history *history);
void	free_temp_input(t_history *history);
int		save_temp_cmd_line(t_history *history, t_line *cmd_line);
int		show_prev_history(t_history *history, t_line *cmd_line);
int		show_next_history(t_history *history, t_line *cmd_line);
int		add_history_line(t_history *history, t_line *cmd_line);

#endif
