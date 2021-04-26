/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/26 14:05:53 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/26 16:49:25 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_utils.h"
#include "cursor.h"

#include <unistd.h>

// int			handle_newline(char **line, t_vector *b)
// {
// 	ssize_t		newline_len;

// 	newline_len = count_newline_len(b);
// 	if (newline_len == NOT_FOUND)
// 	{
// 		if ((b->capacity - b->size) < BUFFER_SIZE)
// 		{
// 			if (!realloc_buffer(b, newline_len))
// 				return (ERROR);
// 		}
// 		return (NOT_FOUND);
// 	}
// 	*line = copy_newline(b->container, newline_len - 1);
// 	if (!*line)
// 	{
// 		free_memory(b);
// 		return (ERROR);
// 	}
// 	if (!realloc_buffer(b, newline_len))
// 		return (ERROR);
// 	return (FOUND);
// }




int	read_command_line(int fd, t_line *line_state)
{
	ssize_t	bytes_read;
//	char	ch;

//	ch = line_state->buf[line_state->line_len];
	bytes_read = read(fd, &line_state->buf[line_state->line_len], 1);
	if (bytes_read == -1)
	{
		return (0);
	}
	if (line_state->buf[line_state->line_len] == CARRIAGE_RETURN) //or to \n?
	{
		line_state->eol = 1;
	}
	else
		line_state->line_len++;
	return (1);
}


