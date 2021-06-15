#ifndef INIT_TERMINAL_DATA_H
# define INIT_TERMINAL_DATA_H

#include "shell_state.h"

int	init_terminal_data(t_shell *shell);
int	get_termcap_codes(char **term_buffer, t_shell *shell);

#endif
