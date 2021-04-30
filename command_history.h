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
** saved_temp_input array is needed to save the copy of the history when its lines are edited but not executed
** it's being cleared after CR/enter/nl is pressed
** + 1 is needed to track the copy of the current command line if the command is typed but not executed yet
*/

typedef struct s_history
{
	char	*lines[MAX_HISTORY];
	char	*saved_temp_input[MAX_HISTORY + 1];
	int		num_lines;
	int		last_shown_line;
	int		is_command_executed;
	int		iter_mode;
}				t_history;

void	init_history(t_history *history);
void	free_history(t_history *history);
void	clear_history(t_history *history);

#endif
