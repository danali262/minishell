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

int	set_input_mode(t_shell *shell)
{
	struct termios	attributes;

	if (!isatty(STDIN_FILENO) || tcgetattr(STDIN_FILENO, &shell->origin_attr) < 0
		|| tcgetattr(STDIN_FILENO, &attributes) < 0)
	{
		errno = ENOTTY;
		return (0);
	}
	attributes.c_lflag &= ~(ICANON | ECHO);
	attributes.c_cc[VTIME] = 0;    
	attributes.c_cc[VMIN] = 1;    
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes) < 0)
	{
		printf("Error. Unable to set one or more terminal attributes.\n");
		return (0);
	}
	if ((attributes.c_lflag & (ECHO | ICANON)))
		return (reset_input_mode(shell, EINVAL));
	return (1);
}

int	reset_input_mode(t_shell *shell, int error_code)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->origin_attr);
	if (error_code == 0)
		return (1);
	else
	{
		errno = error_code;
		return (0);
	}	
}
