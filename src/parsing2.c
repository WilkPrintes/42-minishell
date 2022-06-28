/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:58:24 by lucferna          #+#    #+#             */
/*   Updated: 2022/06/28 22:55:40 by lucferna         ###   ########.fr       */
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
	int	trigger;

	i = 0;
	trigger = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 && trigger == 0)
			trigger = 34;
		else if (ptr[i] == 39 && trigger == 0)
			trigger = 39;
		else if (trigger != 0 && ptr[i] == 7)
			ptr[i] = ' ';
		else if (ptr[i] == trigger)
			trigger = 0;
		i++;
	}
}

void	redirect(char **pars)
{
	int	i;

	i = 0;
	while (pars[i] != NULL)
	{
		if (ft_strncmp(pars[i], ">", ft_strlen(pars[i])) == 0)
		{
			if (pars[i + 1] != NULL)
				open(pars[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
		}
		else if (ft_strncmp(pars[i], ">>", ft_strlen(pars[i])) == 0)
		{
			if (pars[i + 1] != NULL)
				open(pars[i + 1], O_RDWR | O_CREAT | O_APPEND, 0777);
		}
		else if (ft_strncmp(pars[i], "<", ft_strlen(pars[i])) == 0)
		{
			if (pars[i + 1] != NULL)
				open(pars[i + 1], O_RDONLY, 0777);
		}
		i++;
	}
}
