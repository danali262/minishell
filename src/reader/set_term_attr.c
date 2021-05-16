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
** term_attr.c_cc[VMIN] = 1;  will read 1 byte at a time
** [VTIME] = 0; means we are not setting timer
**   And afterwards we're calling set which will install the updated structure
**
** set returns OK if it was able to perform ANY of the requested actions,
** so it is our responsibility to see whether all the requested actions
** were performed:
** we need to call tcgetattr and compare the actual terminal's attributes
** to the desired attributes
** to detect any differences.
*/

int	set_input_mode(struct termios *origin_attr)
{
	struct termios	term_attr;

	if (!isatty (STDIN_FILENO) || tcgetattr(STDIN_FILENO, origin_attr) < 0)
	{
		errno = ENOTTY;
		return (0);
	}
	term_attr = *origin_attr;
	term_attr.c_lflag &= ~(ICANON | ECHO);
	term_attr.c_cc[VMIN] = 1;
	term_attr.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_attr) < 0)
	{
		printf("Error. Unable to set one or more terminal attributes.\n");
		return (0);
	}
	if (tcgetattr(STDIN_FILENO, &term_attr) < 0)
		return (reset_input_mode(origin_attr, EBADF));
	// if ((term_attr.c_lflag & (ECHO | ICANON | ISIG)) || term_attr.c_cc[VMIN] != 1 
	if ((term_attr.c_lflag & (ECHO | ICANON)) || term_attr.c_cc[VMIN] != 1 //replace this string when exit function is implemented
		|| term_attr.c_cc[VTIME] != 0)
		return (reset_input_mode(origin_attr, EINVAL));
	return (1);
}

int	reset_input_mode(struct termios *origin_attr, int error_code)
{
	if (error_code == 0)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, origin_attr);
		return (1);
	}
	else
	{
		tcsetattr(STDIN_FILENO, TCSANOW, origin_attr);
		errno = error_code;
		return (0);
	}	
}
