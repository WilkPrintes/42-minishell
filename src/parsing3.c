/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:55:59 by lucferna          #+#    #+#             */
/*   Updated: 2022/07/15 04:04:28 by lucferna         ###   ########.fr       */
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

void	fix_quotes(char *ptr)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 && trigger == 0)
			trigger = 34;
		else if (ptr[i] == 39 && trigger == 0)
			trigger = 39;
		else if (trigger != 0 && ptr[i] == 32)
			ptr[i] = 7;
		else if (ptr[i] == trigger)
			trigger = 0;
		i++;
	}
}

void	refix_quotes(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 7)
			ptr[i] = ' ';
		i++;
	}
}

int	number_of_commands(char *ptr)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == '|')
			count++;
		i++;
	}
	return (count);
}
