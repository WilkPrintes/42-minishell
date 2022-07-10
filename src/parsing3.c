/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:55:59 by lucferna          #+#    #+#             */
/*   Updated: 2022/07/07 23:50:22 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

char	*remove_quotes(char *ptr, int quote)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(ptr) - 1, sizeof(char));
	while (ptr[i] != '\0')
	{
		if (ptr[i] != quote)
			new[j++] = ptr[i++];
		else
			i++;
	}
	free(ptr);
	return (new);
}
