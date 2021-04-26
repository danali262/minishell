/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cursor.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/25 16:57:30 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/26 12:59:05 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cursor.h"
#include "parsing_utils.h"

#include "libft.h"

# include <unistd.h>
#include <stdio.h>
#include <errno.h>

    // /* Report cursor location */
	// /* Read the response: ESC [ rows ; cols R */
	///* Parse it. */

int	parse_cursor_pos(char *str_start, t_cursor *cursor)
{
	char		**array;
	int			cursor_coordinate;
	int			num_components;

	num_components = 2;
	array = split_into_components(str_start, ';', num_components);
	if (array == NULL)
	{
		errno = EINVAL;
		return (0);
	}
	cursor_coordinate = 0;
	if (is_valid_component(array[0], &cursor_coordinate))
		cursor->row = cursor_coordinate;
	else
		return (0);
	if (is_valid_component(array[1], &cursor_coordinate))
		cursor->col = cursor_coordinate;
	else
		return (0);
	free_array_memory(array);
	return (1);
}

int get_cursor_pos(void)
{
	t_cursor	cursor;
	char		buf[32];
	size_t		i;

	if (write(STDOUT_FILENO, REQUEST_CUR_POS, 4) != 4)
	{
		printf("Error. Can't define cursor location\n");
		return (0);
	}
	i = 0;
	while (buf[i] != 'R')
	{
		read(STDIN_FILENO, buf, 1);
		i++;
    }
    buf[i] = '\0';

	if (buf[0] != ESC || buf[1] != '[')
	{
		printf("Error. Can't define cursor location\n");
		return (0);
	}
	if (!parse_cursor_pos(buf + 2, &cursor))
		return (0);
	return (1);
}
