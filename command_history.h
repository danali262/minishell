#ifndef COMMAND_HISTORY_H
# define COMMAND_HISTORY_H

# define MAX_HISTORY 200

# include <stdlib.h>

/*
** num_lines == number of lines filled
**
** iter_mode stands for iteration mode. In this mode the temp buffer
** is not copied to the bottom of the history.
**
** is_command_executed flag is used to check if the last command in history executed or only saved
*/

typedef struct s_history
{
	char	*lines[MAX_HISTORY];
	int		num_lines;
	int		last_shown_line;
	int		is_command_executed;
	int		iter_mode;
}				t_history;

void	init_history(t_history *history);
void	free_history(t_history *history);

#endif
