
#include "command_history_navigation.h"

#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include <stdio.h>

/*
** The use of static:
** termcap records its address internally for use when you later interrogate
** the description, so you must make sure that its contents remain unchanged
** for as long as you still plan to interrogate the description.
*/

//TODO:
// add the flag -ltermcap to the Makefile to be able to compile with the termcap library

int	init_terminal_data()
{
	char		*term_type;
	static char	term_buffer[2048];
	int			result;

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
	printf("term_buffer: %s\n", term_buffer); //remove
	printf("term_type: %s\n", term_type); //remove
	printf("result: %d\n", result); //remove
	return (1);
}