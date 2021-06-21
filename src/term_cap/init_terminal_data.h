#ifndef INIT_TERMINAL_DATA_H
# define INIT_TERMINAL_DATA_H

# include "shell_state.h"

# define ERROR 1
# define SUCCESS 0

int	init_terminal_data(t_shell *shell);
int	find_term_type_description(char *term_type, char *term_buffer);
int	get_termcap_codes(char **term_buffer, t_shell *shell);

#endif
