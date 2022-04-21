/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes < wprintes@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:12:42 by wprintes          #+#    #+#             */
/*   Updated: 2022/02/11 02:26:28 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	decimal_places(unsigned int i);
static int	potentiation(unsigned int i);
static char	*final(char *s1, unsigned int index, int d_places, unsigned int n);

char	*ft_utoa(unsigned int n)
{
	char			*result;
	int				d_places;
	unsigned int	index;

	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		n = n * (-1);
	d_places = decimal_places(n);
	index = 0;
	result = malloc(sizeof(char) * (d_places + 1));
	if (!result)
		return (NULL);
	return (final(result, index, d_places, n));
}

static int	decimal_places(unsigned int i)
{
	unsigned int	total;
	unsigned int	count;

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

static int	potentiation(unsigned int i)
{
	unsigned int	result;

	result = 1;
	i--;
	while (i > 0)
	{
		result = result * 10;
		i--;
	}
	return (result);
}

static char	*final(char *s1, unsigned int index, int d_places, unsigned int n)
{
	unsigned int	d10;
	char			*result;

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
