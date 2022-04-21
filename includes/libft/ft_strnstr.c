/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wilkp90@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 10:20:13 by wprintes          #+#    #+#             */
/*   Updated: 2021/10/03 20:02:21 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	counter;
	size_t	len_s2;

	counter = 0;
	len_s2 = ft_strlen((char *) s2);
	if (len_s2 == 0)
		return ((char *) s1);
	if (n > 0 && *s1)
	{
		while (counter < n)
		{
			if (len_s2 + counter > n)
				break ;
			if (ft_strncmp((s1 + counter), s2, len_s2) == 0)
				return ((char *) s1 + counter);
			counter++;
		}
	}
	return (NULL);
}
