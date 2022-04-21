/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wilkp90@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 00:39:41 by wprintes          #+#    #+#             */
/*   Updated: 2021/10/04 19:42:58 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t			counter;
	char			*str_p;

	counter = 0;
	str_p = str;
	while (counter != n)
	{
		str_p[counter] = '\0';
		counter++;
	}
}
