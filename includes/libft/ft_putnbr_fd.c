/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wilkp90@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 00:09:30 by wprintes          #+#    #+#             */
/*   Updated: 2021/10/01 08:24:33 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	decimal_places(long i);
static int	potentiation(int i);

void	ft_putnbr_fd(int n, int fd)
{
	int		d_places;
	int		d10;
	long	result;
	char	temp;

	result = n;
	if (n < 0)
	{
		temp = '-';
		result = result * -1;
		write(fd, &temp, 1);
	}
	d_places = decimal_places(result);
	d10 = potentiation(d_places);
	while (d_places > 0)
	{
		temp = result / d10 + '0';
		result = result % d10;
		d10 = d10 / 10;
		d_places--;
		write(fd, &temp, 1);
	}
}

static int	potentiation(int i)
{
	int	result;

	result = 1;
	i--;
	while (i > 0)
	{
		result = result * 10;
		i--;
	}
	return (result);
}

static int	decimal_places(long i)
{
	int	total;
	int	count;

	if (i == 0)
		return (1);
	count = 0;
	total = 0;
	while (i > 0)
	{
		i = i / 10;
		total = 10 * 10;
		count++;
	}
	return (count);
}
