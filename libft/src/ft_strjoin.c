/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 08:46:17 by osamara       #+#    #+#                 */
/*   Updated: 2020/11/16 19:09:54 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*joined_str;
	size_t		joined_len;
	const char	*str1;
	const char	*str2;

	if (!s1 || !s2)
		return (NULL);
	str1 = s1;
	str2 = s2;
	joined_len = (ft_strlen(str1) + ft_strlen(str2));
	joined_str = (char *)malloc(sizeof(char) * (joined_len + 1));
	if (joined_str == NULL)
		return (NULL);
	ft_strlcpy(joined_str, str1, joined_len + 1);
	ft_strlcat(joined_str, str2, joined_len + 1);
	return (joined_str);
}
