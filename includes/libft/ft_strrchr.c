/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wilkp90@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 00:40:45 by wprintes          #+#    #+#             */
/*   Updated: 2021/10/03 20:01:14 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char			*str_result;
	unsigned char	c_text;

	c_text = c;
	str_result = NULL;
	while (*str != '\0')
	{
		if (*str == c_text)
			str_result = (char *) str;
		str++;
	}
	if (c == '\0')
		return ((char *) str);
	return (str_result);
}
