/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wilkp90@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:13:54 by wprintes          #+#    #+#             */
/*   Updated: 2021/10/03 20:02:03 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	counter;

	counter = 0;
	len_dest = ft_strlen ((char *) dest);
	len_src = ft_strlen ((char *) src);
	if (destsize >= len_dest + 1)
	{
		while ((len_dest + counter) < (destsize - 1) && src[counter] != '\0')
		{
			dest[len_dest + counter] = src[counter];
			counter++;
		}
		dest[len_dest + counter] = '\0';
	}
	if (destsize < len_dest)
		return (len_src + destsize);
	return (len_src + len_dest);
}
