/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/26 14:05:53 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/27 07:25:02 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_utils.h"
#include "cursor.h"

#include "libft.h"

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
	char	ch;

	ch = 0;
	bytes_read = read(fd, &ch, 1);
	if (bytes_read == -1)
	{
		return (0);
	}
	if (ft_isprint(ch))
	{
		write(STDOUT_FILENO, &ch, 1);
		line_state->buf[line_state->line_len] = ch;
		line_state->line_len++;
	}
	else if (ch == NEWLINE)
	{
		line_state->eol = 1;
	}
	return (1);
}
