/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes < wprintes@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:14:11 by wprintes          #+#    #+#             */
/*   Updated: 2022/02/11 02:39:02 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join(char *s1_val, char *s2_val, char *result);

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*result;
	char	*s1_val;
	char	*s2_val;

	if (!s1 || !s2)
		return (NULL);
	s1_val = (char *)s1;
	s2_val = (char *)s2;
	result = malloc(sizeof(char) * (ft_strlen(s1_val) + ft_strlen(s2_val)) + 1);
	if (result == NULL)
		return (NULL);
	result = join(s1_val, s2_val, result);
	return (result);
}

char	*join(char *s1_val, char *s2_val, char *result)
{
	size_t	counter;

	counter = 0;
	while (s1_val[counter] != '\0')
	{
		result[counter] = s1_val[counter];
		counter++;
	}
	counter = 0;
	while (s2_val[counter] != '\0')
	{
		result[ft_strlen(s1_val) + counter] = s2_val[counter];
		counter++;
	}
	result[ft_strlen(s1_val) + counter] = '\0';
	return (result);
}
