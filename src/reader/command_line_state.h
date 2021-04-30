/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_line_state.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/26 13:36:57 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/30 10:10:23 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LINE_STATE_H
#define COMMAND_LINE_STATE_H

# include <stddef.h>
# include <limits.h>

# define BUF_SIZE ARG_MAX

typedef struct s_line
{
	char	*buf;
	size_t	line_len;
}				t_line;

int	init_command_line(t_line *line_state);
int	clear_command_line(t_line *line_state);
void	free_command_line(t_line *line_state);


#endif
