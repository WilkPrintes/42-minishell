/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:46:25 by lucferna          #+#    #+#             */
/*   Updated: 2022/06/07 00:53:58 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static int	have_quotes(char *ptr)
{
	int	val;
	int	i;

	val = 0;
	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 || ptr[i] == 39)
			val++;
		i++;
	}
	if (val % 2 != 0)
		return (-1);
	else if (val == 0)
		return (0);
	return (1);
}

static void	fix_quotes(char *ptr)
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

static void	refix_quotes(char *ptr)
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


int	parse(char *ptr, char **pars)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = have_quotes(ptr);
	if (quotes == -1)
		return (write(2, "error\n", 6));
	else if (quotes == 1)
		fix_quotes(ptr);
	pars = ft_split(ptr, ' ');
	while (1)
	{
		if (pars[i] == NULL)
			break;
		if (ft_strchr(pars[i], 7) != NULL)
			refix_quotes(pars[i]);
		i++;
	}
	refix_quotes(ptr);
	redirect(pars);
	return (0);
}
