/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wilkp90@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 00:40:33 by wprintes          #+#    #+#             */
/*   Updated: 2021/10/04 19:42:22 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			counter;
	char			*str_p;
	unsigned char	c_value;

	counter = 0;
	str_p = str;
	c_value = c;
	while (counter != n)
	{
		str_p[counter] = c_value;
		counter++;
	}
	return (str);
}
