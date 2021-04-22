/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_term_attr.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/22 17:02:02 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/22 18:09:18 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

/* origin_attr is used to remember original terminal attributes. */

// void    reset_input_mode (struct termios *origin_attr)
// {
//   tcsetattr (STDIN_FILENO, TCSANOW, origin_attr);
// }

void
set_input_mode (void)
{
  struct termios origin_attr;
  struct termios term_attr;

/* Make sure stdin is a terminal.
** determines if the file descriptor refers to a valid terminal type device.
*/
  if (!isatty (STDIN_FILENO) || tcgetattr(STDIN_FILENO, &origin_attr) < 0)
    {
        printf("Error.Not a terminal.\n");
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

  tcgetattr (STDIN_FILENO, &term_attr);
  term_attr.c_lflag &= ~(ICANON|ECHO);
  term_attr.c_cc[VMIN] = 1;
  term_attr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &term_attr);

//   do I need to reset the original attributes if anything fails and when I exit the program?
// reset_input_mode (struct termios *origin_attr);
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
