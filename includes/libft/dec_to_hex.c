/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes < wprintes@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:30:10 by wprintes          #+#    #+#             */
/*   Updated: 2022/02/11 02:16:42 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	hex_places(unsigned int a);
int	init(unsigned int a, int cap);

int	dec_to_hex(unsigned int a, int cap)
{
	char			*result;
	unsigned int	temp;
	int				places;

	places = 0;
	if (init(a, cap) != 0)
		return (1);
	places = hex_places(a);
	result = malloc(sizeof(char) * places + 1);
	result[places] = '\0';
	while (places > 0)
	{
		temp = (a % 16);
		if (temp < 10)
			result[places - 1] = temp + '0';
		else
			result[places - 1] = (cap + temp);
		a = a / 16;
		places--;
	}
	places = ft_putstr(result);
	free(result);
	return (places);
}

int	hex_places(unsigned int a)
{
	unsigned int	temp;
	int				places;

	temp = a;
	places = 0;
	while (temp > 0)
	{
		temp = temp / 16;
		places++;
	}
	return (places);
}

int	init(unsigned int a, int cap)
{
	if (a < 16)
	{
		if (a < 10)
			ft_putchar (a + '0');
		else
			ft_putchar (a + cap);
		return (1);
	}
	else
		return (0);
}
