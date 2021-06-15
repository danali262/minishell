#include "init_terminal_data.h"
#include "termcap_codes.h"

#include "libft.h"

#include <curses.h>
#include <term.h>
#include <termcap.h>
#include <unistd.h>
#include <stdlib.h>

/*
** The use of static char	*term_buffer:
** termcap records its address internally for use when you later interrogate
** the description, so you must make sure that its contents remain unchanged
** for as long as you still plan to interrogate the description.
*/

int	init_terminal_data(t_shell *shell)
{
	char		*term_type;
	static char	*term_buffer;
	int			result;

	term_buffer = malloc(2048);
	if (!term_buffer)
		return (0);
	shell->term_buffer = term_buffer;
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
	if (!get_termcap_codes(&term_buffer, shell))
		return (0);
	return (1);
}

/*
**	tgetstr will return code value or 0 if it is not available
*/

int	get_termcap_codes(char **term_buffer, t_shell *shell)
{	
	shell->termcap_codes.keyup = tgetstr("ku", term_buffer);
	shell->termcap_codes.keydown = tgetstr("kd", term_buffer);
	if (shell->termcap_codes.keyup  == 0 || shell->termcap_codes.keydown == 0)
	{
		ft_putstr_fd("Error. Terminal capabilities unavailable.\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}
