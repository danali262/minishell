#include "init_terminal_data.h"

#include <curses.h>
#include <term.h>
#include <termcap.h>
#include <stdio.h>
# include <stdlib.h>


/*
** The use of static char	*term_buffer:
** termcap records its address internally for use when you later interrogate
** the description, so you must make sure that its contents remain unchanged
** for as long as you still plan to interrogate the description.
*/


int	init_terminal_data(void)
{
	char		*term_type;
	static char	*term_buffer;
	int			result;

	term_buffer = malloc(2048);
	term_type = getenv("TERM");
	if (term_type == NULL)
	{
		printf("The terminal type is not defined.");
		return (0);
	}
	result = tgetent(term_buffer, term_type);
	if (result < 0)
	{
		printf("The termcap database cannot be found.");
		return (0);
	}
	else if (result == 0)
	{
		printf("The terminal type is not defined.");
		return (0);
	}
	char *temp = tgetstr ("ku", &term_buffer);
	char *temp1 = tgetstr ("kd", &term_buffer);
	printf("ku: %s\n", temp); //remove
	printf("kd: %s\n", temp1); //remove

	return (1);
}