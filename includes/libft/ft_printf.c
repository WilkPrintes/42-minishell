/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes < wprintes@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:43:09 by wprintes          #+#    #+#             */
/*   Updated: 2022/02/11 02:16:48 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	arg_flags(char *s, int count, va_list args);

int	ft_printf(const char *s, ...)
{
	va_list	paramets;
	int		count;
	int		total;

	count = 0;
	total = 0;
	va_start(paramets, s);
	while (s[count] != '\0')
	{
		if (s[count] == '%' && ft_strchr("cspdiuxX%", s[count + 1]))
		{
			total = total + arg_flags((char *)s, count + 1, paramets);
			count++;
		}
		else
		{
			write(1, &s[count], 1);
			total++;
		}
		count++;
	}
	va_end(paramets);
	return (total);
}

int	arg_flags(char *s, int count, va_list args)
{
	int		total;
	char	*temp;

	total = 0;
	temp = NULL;
	if (s[count] == 's')
		total = ft_putstr(va_arg(args, char *));
	else if (s[count] == 'c')
		total = ft_putchar(va_arg(args, int));
	else if (s[count] == 'd' || s[count] == 'i')
		temp = ft_itoa(va_arg(args, int));
	else if (s[count] == 'u')
		temp = ft_utoa(va_arg(args, int));
	else if (s[count] == 'x')
		total = dec_to_hex(va_arg(args, unsigned int), 87);
	else if (s[count] == 'X')
		total = dec_to_hex(va_arg(args, unsigned int), 55);
	else if (s[count] == '%')
		total = ft_putchar('%');
	else if (s[count] == 'p')
		total = dec_to_hex_l((unsigned long int) va_arg(args, void *), 87);
	if (temp != NULL)
		total = ft_putstr(temp);
	free(temp);
	return (total);
}
