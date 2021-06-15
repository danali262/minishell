#include "read_command_line.h"

#include "command_line_state.h"
#include "termcap.h"
#include "../command_history/command_history.h"

#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

/* origin_attr is used to remember original terminal attributes
**
** isatty makes sure stdin is a terminal.
**
** We have to turn off ICANON and ECHO
** and interpret the escape sequences from the arrow keys on our own.
**
**   And afterwards we're calling set which will install the updated structure
**
*/

int	set_input_mode(struct termios *origin_attr)
{
	if (!isatty (STDIN_FILENO) || tcgetattr(STDIN_FILENO, origin_attr) < 0)
	{
		errno = ENOTTY;
		return (0);
	}
	(*origin_attr).c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, origin_attr) < 0)
	{
		printf("Error. Unable to set one or more terminal attributes.\n");
		return (0);
	}
	if (((*origin_attr).c_lflag & (ECHO | ICANON)))
		return (reset_input_mode(origin_attr, EINVAL));
	return (1);
}

int	reset_input_mode(struct termios *origin_attr, int error_code)
{
	(*origin_attr).c_lflag |= (ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, origin_attr);
	if (error_code == 0)
		return (1);
	else
	{
		errno = error_code;
		return (0);
	}	
}
