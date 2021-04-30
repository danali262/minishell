/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 15:19:51 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:21:11 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	char_found(char const *set, char character)
{
	int	j;

	j = 0;
	while (set[j] != 0)
	{
		if (character == set[j])
		{
			return (1);
		}
		else
			j++;
	}
	return (0);
}

static char	*find_start(char const *s1, char const *set)
{
	char	*start;

	start = ((char *)s1);
	while (*start != 0)
	{
		if (!char_found(set, *start))
			break ;
		else
			start++;
	}
	return (start);
}

static char	*find_end(char *start, char const *set)
{
	int		len;
	char	*end;

	len = ((int)ft_strlen(start));
	end = start + len;
	while (end > start)
	{
		end--;
		if (!char_found(set, *end))
		{
			break ;
		}
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s_trimmed;
	char	*ptr;
	char	*start;
	char	*end;

	if (!s1)
		return (NULL);
	start = find_start(s1, set);
	if (*start == '\0')
		end = start - 1;
	else
		end = find_end(start, set);
	s_trimmed = (char *)malloc(sizeof(char) * (end - start) + 2);
	if (s_trimmed == NULL)
		return (NULL);
	ptr = s_trimmed;
	while (start <= end)
	{
		*ptr = *start;
		start++;
		ptr++;
	}
	*ptr = '\0';
	return (s_trimmed);
}
