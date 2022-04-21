/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wilkp90@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:45:36 by wprintes          #+#    #+#             */
/*   Updated: 2021/10/04 20:48:54 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	counter;
	char	*a;

	if (!s)
		return (NULL);
	a = ft_strdup(s);
	if (!a)
		return (NULL);
	counter = 0;
	while (a[counter] != '\0')
	{
		a[counter] = f(counter, a[counter]);
		counter++;
	}
	return (a);
}
