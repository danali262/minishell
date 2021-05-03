#ifndef PARSER_H
# define PARSER_H

#include "../reader/command_line_state.h"

// typedef struct	s_simplecommand
// {
// 	char	*command;
// 	char	*arg;
//     char    *last_element;      /* ought to be NULL, we will be using this array to provide input to execve */
// 	char	*input;
// 	char	*output;
// 	char	*err;
// }				t_simplecommand;
// 
// t_simplecommand	    *command_table;

int	parse_command_line(t_line *cmd_line);



#endif
