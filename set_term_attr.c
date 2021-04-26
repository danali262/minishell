/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_term_attr.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/22 17:02:02 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/26 10:21:42 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cursor.h"

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

// TODO: You have to keep your own “actual” buffer of what's on the screen and where the cursor is.
// You also need a “desired” buffer of what you want on the screen and where you want the cursor.
// These buffers don't cover the whole screen, just the lines containing your prompt
// and the user's input (which you echoed manually because you turned off ECHO).
//  Since you printed everything on these lines, you know their contents.


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
if (!get_cursor_pos())
{
	return(reset_input_mode(&origin_attr, EINVAL));
}
//  I need to reset the original attributes if anything fails and when I exit the program
	return (1);
}

int
main (void)
{
  char c;

  set_input_mode ();

  while (1)
    {
      read (STDIN_FILENO, &c, 1);
      if (c == '\004')          /* Ctrl d */
        break;
      else
        putchar (c); //or start parsing and executing
    }

  return EXIT_SUCCESS;
}
