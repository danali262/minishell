/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_term_attr.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/22 17:02:02 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/30 09:42:00 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "set_term_attr.h"
#include "cursor.h"
#include "gnl_utils.h"
#include "command_history.h"
#include "command_line_state.h"
#include "termcap.h"

#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/errno.h>

/* origin_attr is used to remember original terminal attributes. */

int	reset_input_mode (struct termios *origin_attr, int error_code)
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

int    set_input_mode (void)
{
  struct termios origin_attr;
  struct termios term_attr;

/* Make sure stdin is a terminal.
** determines if the file descriptor refers to a valid terminal type device.
*/
  if (!isatty (STDIN_FILENO) || tcgetattr(STDIN_FILENO, &origin_attr) < 0)
    {
        errno = ENOTTY;
        return(0);
    }
/*
** We have to turn off ICANON and ECHO
** and interpret the escape sequences from the arrow keys on our own.
*/

  term_attr = origin_attr;
  term_attr.c_lflag &= ~(ICANON | ECHO); 
  term_attr.c_cc[VMIN] = 1; // 1 byte at a time
  term_attr.c_cc[VTIME] = 0; // no timer
  //calling set will install the updated structure
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_attr) < 0)
  {
  		printf("Error. Unable to set one or more terminal attributes.\n");
        return(0);
  }
    //  This function returns OK if it was able to perform any of the requested actions,
//  even if it couldn't perform all the requested actions. If the function returns OK,
//  it is our responsibility to see whether all the requested actions were performed.
  //This means that after we call tcsetattr to set the desired attributes, 
  //we need to call tcgetattr and compare the actual terminal's attributes to the desired attributes
  //to detect any differences.
if (tcgetattr(STDIN_FILENO, &term_attr) < 0)
{
	return(reset_input_mode(&origin_attr, EBADF));
}
if ((term_attr.c_lflag & (ECHO | ICANON)) || term_attr.c_cc[VMIN] != 1 ||
	term_attr.c_cc[VTIME] != 0)
{
	return(reset_input_mode(&origin_attr, EINVAL));
}
if (!get_cursor_pos()) // do I need it for the mandatory part?
{
	return(reset_input_mode(&origin_attr, EINVAL));
}
	return (1);
}


int	main (void)
{
	t_history	history;
	t_line		line_state;

	set_input_mode();
	init_terminal_data();
	if (!init_command_line(&line_state))
		return (1);
    init_history(&history);
	clear_command_line(&line_state);
	while (1)
	{
        write(STDOUT_FILENO, "bash-3.2$ ", 10);
		while (history.is_command_executed != 1)
		{
			if (!read_command_line(STDIN_FILENO, &history, &line_state))
			{
				free_command_line(&line_state);
				free_history(&history);
				return (1); //will be returning - 1
			}
		}
		// if (line_state.line_len != 0)
		printf("here is the execution result printed...\n");//remove
		history.is_command_executed = 0;
		//start parsing and executing
		//print execution result
		// print promt
		printf("%s", line_state.buf); //remove it, need for debugging
	}
	return (0);
}
