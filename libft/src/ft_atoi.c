/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 20:22:35 by osamara       #+#    #+#                 */
/*   Updated: 2021/06/14 14:45:43 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			index;
	int			is_minus;
	long long	int_accumulator;

	index = 0;
	is_minus = 0;
	int_accumulator = 0;
	while (str[index] != '\0' && (str[index] == '\t' || str[index] == '\n'
			|| str[index] == '\v' || str[index] == '\f'
			|| str[index] == '\r' || str[index] == ' '))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			is_minus = !is_minus;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		int_accumulator = int_accumulator * 10 + (str[index] - '0');
		index++;
	}
	if (is_minus)
		int_accumulator = -int_accumulator;
	return ((int)int_accumulator);
}

/*
** index >= start_index + 10
** 10 == num of digits in max int
** checking that no long long is passed
*/

int	ft_printf_atoi(const char *start, int *num)
{
	int			index;
	int			ptr;
	long long	accumulator;
	int			start_index;

	index = 0;
	accumulator = 0;
	while (start[index] == '0')
		index++;
	start_index = index;
	while (start[index] >= '0' && start[index] <= '9')
	{
		ptr = start[index] - '0';
		accumulator = accumulator * 10 + ptr;
		index++;
	}
	if (accumulator > 2147483647 || index >= start_index + 10
		|| start[index] != '\0')
	{
		*num = 0;
		return (0);
	}
	else
		*num = index;
	return ((int)accumulator);
}

// static int	handle_accumulator(long long accumulator, int *num, int is_minus, int index)
// {
// 	
// }

static int	handle_negative_num(char c, int *index)
{
	if (c== '-')
    {
		*index = *index + 1;
		return (1);
	}
	return (0);
}

int	ft_minishell_atoi(char *start, int *num)
{
	int			index;
	int			is_minus;
	long long	accumulator;

	index = 0;
	accumulator = 0;
	is_minus = handle_negative_num(start[index], &index);
	while (start[index] >= '0' && start[index] <= '9')
	{
		accumulator = accumulator * 10 + start[index] - '0';
		index++;
	}
	if (is_minus)
		accumulator = -accumulator;
	if (accumulator > 2147483647 || start[index] != '\0'
		|| (is_minus && index == 1))
	{
		*num = 0;
		return (0);
	}
	else
		*num = index;
	return ((int)accumulator);
}
