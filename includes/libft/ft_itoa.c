/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wilkp90@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:50:58 by wprintes          #+#    #+#             */
/*   Updated: 2021/10/03 18:56:47 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	decimal_places(int i);
static int	potentiation(int i);
static char	*final(char *s1, int index, int d_places, int n);

char	*ft_itoa(int n)
{
	char	*result;
	int		negative;
	int		d_places;
	int		index;

	negative = 0;
	if (n == 0)
		return (ft_substr("0", 0, 1));
	if (n == -2147483648)
		return (ft_substr("-2147483648", 0, 11));
	if (n < 0)
		n = n * (-1) + negative++;
	d_places = decimal_places(n);
	index = 0;
	result = ft_calloc(sizeof(char), d_places + negative + 1);
	if (!result)
		return (NULL);
	if (negative == 1)
	{
		result[0] = '-';
		index++;
	}
	return (final(result, index, d_places, n));
}

static int	decimal_places(int i)
{
	int	total;
	int	count;

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

static char	*final(char *s1, int index, int d_places, int n)
{
	int		d10;
	char	*result;

	result = s1;
	d10 = potentiation(d_places);
	while (d_places > 0)
	{
		result[index] = n / d10 + '0';
		n = n % d10;
		d10 = d10 / 10;
		d_places--;
		index++;
	}
	result[index] = '\0';
	return (result);
}
