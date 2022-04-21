/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes < wprintes@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 08:24:03 by wprintes          #+#    #+#             */
/*   Updated: 2022/02/11 02:40:57 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	counter_c(char *s, char c);
static char		**test(char *s, char **result, size_t separator, char c);
static void		init_var(size_t *a, size_t *b, size_t *c);

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	separator;

	if (!s)
		return (NULL);
	separator = counter_c((char *) s, c);
	result = ft_calloc(separator + 1, sizeof(char *));
	if (separator == 1)
	{
		result[0] = ft_strtrim((char *) s, &c);
		result[1] = NULL;
		return (result);
	}
	if (result == NULL)
		return (NULL);
	return (test((char *)s, result, separator, c));
}

static size_t	counter_c(char *s, char c)
{
	int	result;

	result = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			while (*s != c && *s != '\0')
				s++;
			result++;
		}
		else
			s++;
	}
	return (result);
}

static char	**test(char *s, char **result, size_t separator, char c)
{
	size_t	count;
	size_t	temp;
	size_t	index_r;

	init_var(&count, &temp, &index_r);
	while (s[count] != '\0' && separator != 0)
	{
		if (s[count] == c)
		{
			if (count != 0 || separator == 1)
			{
				result[index_r++] = ft_substr(s, temp, count - temp);
				separator--;
			}
			while (s[count] == c)
				count++;
			temp = count;
		}
		else
			count++;
	}
	if (separator != 0)
		result[index_r] = ft_substr(s, temp, count - temp);
	return (result);
}

static void	init_var(size_t *a, size_t *b, size_t *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}
