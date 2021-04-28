/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_state.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/26 13:36:57 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/28 16:34:32 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_STATE_H
# define LINE_STATE_H

# include <stddef.h>
# include <limits.h>

# define BUF_SIZE ARG_MAX

typedef struct s_line
{
	char	*buf;
	int		eol;
	size_t	line_len;
}				t_line;

int	init_buffer(t_line *line_state);
void	free_buffer(t_line *line_state);
int	reset_line_state(t_line *line_state);


#endif
