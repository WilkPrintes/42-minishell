/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:04:17 by wprintes          #+#    #+#             */
/*   Updated: 2022/07/13 23:25:08 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	find_n(char *buffer)
{
	size_t	counter;

	counter = 0;
	while (buffer[counter] != '\0' && buffer[counter] != '\n')
		counter++;
	return (counter);
}
