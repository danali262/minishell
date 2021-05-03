/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/23 16:52:28 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/28 15:19:16 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"

#include "libft.h"

#include <stdlib.h>

int	is_valid_component(const char *string, int *component)
{
	int		num_chars;
	int		accumulator;
	int		is_valid_component;
	char	*trimmed_string;

	num_chars = 0;
	is_valid_component = 1;
	trimmed_string = ft_strtrim(string, " R");
	accumulator = ft_printf_atoi(trimmed_string, &num_chars);
	if (trimmed_string[num_chars] != 0 || num_chars == 0)
	{
		is_valid_component = 0;
	}
	*component = accumulator;
	free(trimmed_string);
	return (is_valid_component);
}

char	**split_into_components(char *line, char separator,
	int num_components)
{
	char	**array;
	int		i;

	array = ft_split(line, separator);
	if (array == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (array[i] != NULL)
	{
		i++;
	}
	if (i != num_components)
	{
		free_array_memory(array);
		return (NULL);
	}
	return (array);
}
