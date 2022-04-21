/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wilkp90@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 00:40:35 by wprintes          #+#    #+#             */
/*   Updated: 2021/10/03 17:41:10 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	s1;

	s1 = c;
	while (*str != '\0')
	{
		if (*str == s1)
			return ((char *) str);
		str++;
	}
	if (s1 == '\0')
		return ((char *) str);
	return (NULL);
}
