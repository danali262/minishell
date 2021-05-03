/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 13:18:20 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:25:09 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_strings(char const *ch, char sep)
{
	int	count;
	int	char_between_sep;

	count = 0;
	char_between_sep = 0;
	while (*ch != '\0')
	{
		if (*ch != sep)
		{
			char_between_sep = 1;
		}
		else
		{
			if (char_between_sep == 1)
			{
				count++;
			}
			char_between_sep = 0;
		}
		ch++;
	}
	if (char_between_sep)
		count++;
	return (count);
}

static void	free_memory(char **array, int string_index)
{
	int	count;

	count = 0;
	while (string_index > count)
	{
		free(array[string_index]);
		string_index--;
	}
	free(array);
}

static int	fill_string(char **array, char const *ch, char sep, int index)
{
	size_t	char_count;

	char_count = 0;
	while (*ch != sep && *ch != '\0')
	{
		char_count++;
		ch++;
	}
	array[index] = (char *)malloc(sizeof(char) * (char_count + 1));
	if (array[index] == NULL)
	{
		free_memory(array, index);
		return (-1);
	}
	ft_memcpy(array[index], ch - char_count, char_count);
	*(array[index] + char_count) = '\0';
	return (((int)char_count));
}

char	**ft_split(char const *str, char sep)
{
	char	**array;
	int		string_index;
	int		str_number;
	int		str_len;

	if (!str)
		return (NULL);
	str_number = count_strings(str, sep);
	array = (char **)malloc(sizeof(char *) * (str_number + 1));
	if (array == NULL)
		return (NULL);
	string_index = 0;
	while (string_index < str_number)
	{
		while (*str == sep)
			str++;
		str_len = fill_string(array, str, sep, string_index);
		if (str_len == -1)
			return (NULL);
		str += (str_len + 1);
		string_index++;
	}
	array[string_index] = NULL;
	return (array);
}
