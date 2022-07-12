/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:58:24 by lucferna          #+#    #+#             */
/*   Updated: 2022/07/12 21:21:58 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

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

int	have_quotes(char *ptr)
{
	int	i;
	int	val;
	int	quotes;

	i = 0;
	val = 0;
	quotes = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 || ptr[i] == 39)
		{
			val++;
			quotes = ptr[i++];
			while (ptr[i] != '\0' && ptr[i] != quotes)
				i++;
			if (ptr[i] == quotes)
				val++;
		}
		i++;
	}
	if (val % 2 != 0)
		return (-1);
	else if (val == 0)
		return (0);
	return (1);
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

static void	redirections(char **ptr)
{
	int	i;
	int	len;

	i = 0;
	while (ptr[i] != NULL)
	{
		len = ft_strlen(ptr[i]);
		if (ft_strncmp(ptr[i], ">", len) == 0 && ptr[i + 1] != NULL)
			open(ptr[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
		else if (ft_strncmp(ptr[i], ">>", len) == 0 && ptr[i + 1] != NULL)
			open(ptr[i + 1], O_RDWR | O_CREAT | O_APPEND, 0777);
		else if (ft_strncmp(ptr[i], "<", len) == 0 && ptr[i + 1] != NULL)
			open(ptr[i + 1], O_RDONLY, 0777);
		else if (ft_strncmp(ptr[i], "<<", len) == 0 && ptr[i + 1] != NULL)
		{
			read(0, ttyname(0), 200);
		}
		i++;
	}
}

void	redirect(char *ptr)
{
	int		i;
	char	**hold;

	if (ptr[0] == '\0')
		return ;
	i = 0;
	hold = ft_split(ptr, ' ');
	while (hold[i] != NULL)
	{
		if (have_quotes(hold[i]) == 1)
			hold[i] = remove_quotes(hold[i]);
		refix_quotes(hold[i++]);
	}
	redirections(hold);
	free_this(hold);
}

