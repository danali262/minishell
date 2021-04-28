#ifndef COMMAND_HISTORY_H
# define COMMAND_HISTORY_H

# define MAX_HISTORY 200

# include <stdlib.h>

typedef struct s_history
{
	char	*lines[MAX_HISTORY];
	int		last_line_index;
}				t_history;

void	init_history(t_history *history);
void	free_history(t_history *history);

#endif
