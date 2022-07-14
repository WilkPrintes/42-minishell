/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:55:59 by lucferna          #+#    #+#             */
/*   Updated: 2022/07/11 23:48:02 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

char	*remove_quotes(char *ptr)
{
	int		i;
	int		j;
	int		quotes;
	char	*new;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(ptr) - 1, sizeof(char));
	if (ptr[0] == 34 || ptr[0] == 39)
		quotes = ptr[0];
	else
		quotes = 0;
	while (ptr[i] != '\0')
	{
		if (quotes != 0 && ptr[i] != quotes)
			new[j++] = ptr[i++];
		else if (quotes == 0 && ptr[i] != 39 && ptr[i] != 34)
			new[j++] = ptr[i++];
		else
			i++;
	}
	free(ptr);
	return (new);
}
