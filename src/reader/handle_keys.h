#ifndef HANDLE_KEYS_H
# define HANDLE_KEYS_H

# include "shell_state.h"
# include "../command_history/command_history.h"
# include "command_line_state.h"

int		handle_enter(t_shell *shell);
void	handle_backspace(t_line *cmd_line);
int		handle_eot(t_history *history, t_line *cmd_line);

#endif
