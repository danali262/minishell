#ifndef HISTORY_STATE_H
# define HISTORY_STATE_H

# define MAX_HIST 200

/*
** num_lines == number of lines filled
**
** iter_mode stands for iteration mode. In this mode the temp buffer
** is not copied to the bottom of the history.
**
*/

typedef struct s_history
{
	char	*lines[MAX_HIST];
	char	*saved_temp_input[MAX_HIST + 1];
	int		num_lines;
	int		last_shown_line;
	int		iter_mode;
}				t_history;

#endif
