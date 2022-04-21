/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes < wprintes@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:57:25 by wprintes          #+#    #+#             */
/*   Updated: 2022/02/11 02:25:13 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (s)
	{
		while (s[count] != '\0')
		{
			write(1, &s[count], 1);
			count++;
		}
	}
	else
		return (ft_putstr("(null)"));
	return (count);
}

int	ft_putchar(const int c)
{
	write(1, &c, 1);
	return (1);
}

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
