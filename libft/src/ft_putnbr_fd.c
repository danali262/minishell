/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 17:25:36 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:28:19 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static	void	print_recursively(int nb, int fd)
{
	int	digit_to_print;

	if (nb > 0)
	{
		print_recursively(nb / 10, fd);
		digit_to_print = nb % 10 + '0';
		write(fd, &digit_to_print, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	else if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		print_recursively(n, fd);
	}
}
