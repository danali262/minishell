#ifndef SIGNALS_H
# define SIGNALS_H

# include "shell_state.h"

void	catch_signals(void);
void	quit_execution(int signum);

#endif
