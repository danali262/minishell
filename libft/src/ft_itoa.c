/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 15:58:20 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:14:29 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_negative(long long n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static int	count_str_length(long long n)
{
	int		str_length;

	str_length = 0;
	if (n == 0)
	{
		str_length = 1;
	}
	if (is_negative(n))
	{
		str_length = 1;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		str_length++;
	}
	return (str_length);
}

static void	convert_digit(long long n, char *digit)
{
	*digit = '\0';
	digit--;
	while (n > 0)
	{
		*digit = n % 10 + '0';
		digit--;
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	int			str_length;
	char		*str_start;
	char		*digit;
	long long	number;

	number = ((long long)n);
	str_length = count_str_length(number);
	str_start = (char *)malloc(sizeof(char) * (str_length + 1));
	if (str_start == NULL)
		return (NULL);
	if (number == 0)
		*str_start = '0';
	if (is_negative(number))
	{
		*str_start = '-';
		number = -number;
	}
	digit = str_start + str_length;
	convert_digit(number, digit);
	return (str_start);
}
