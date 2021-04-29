#ifndef COMMAND_HISTORY_H
# define COMMAND_HISTORY_H

# define MAX_HISTORY 200

# include <stdlib.h>

/*
** num_lines == number of lines filled
*/

typedef struct s_history
{
	char	*lines[MAX_HISTORY];
	int		num_lines;
	int		last_shown_line;
	int		iter_mode;
}				t_history;

void	init_history(t_history *history);
void	free_history(t_history *history);

#endif
