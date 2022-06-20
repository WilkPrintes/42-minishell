/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:46:25 by lucferna          #+#    #+#             */
/*   Updated: 2022/06/20 20:34:10 by lucferna         ###   ########.fr       */
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

int		number_of_commands(char *ptr)
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

int		cmd_malloc(char *ptr, int cmd_nb)
{
	int	i;
	int	size;
	int	trigger;

	i = 0;
	size = 0;
	trigger = 1;
	while (cmd_nb != 0)
	{
		if (ptr[i] == '|')
			cmd_nb--;
		i++;
	}
	while (ptr[i] != '\0' && ptr[i] != '|')
	{
		if (ptr[i] == ' ' && trigger == 1)
			trigger = 0;
		else if (ptr[i] == '-' && ft_isalpha(ptr[i + 1]))
			trigger = 1;
		if (trigger == 1)
			size++;
		i++;
	}
	return (size);
}

char	*cpy_cmd(char *ptr, int cmd_nb)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = calloc(cmd_malloc(ptr, cmd_nb), sizeof(char));
	while (ptr[i] != '\0' && cmd_nb != 0)
	{
		if (ptr[i++] == '|')
			cmd_nb--;
	}
	while (ptr[i] != '\0' && ptr[i] != '|' && ptr[i] != ' ')
		new[j++] = ptr[i++];
	while (ptr[i] != '\0' && ptr[i] != '|' && ptr[i - 1] != 0)
	{
		if (ptr[i] == '-')
		{
			new[j++] = ' ';
			while (ptr[i] != ' ' && ptr[i] != '\0' && ptr[i] != '|')
				new[j++] = ptr[i++];
		}
		i++;
	}
	return (new);
}

int	parse(char *ptr, t_main *bingo)
{
	int	pipe;
	int	i;

	i = 0;
	pipe = number_of_commands(ptr);
	bingo->cmds = malloc((pipe + 1) * sizeof(char *));
	while (i != pipe)
	{
		bingo->cmds[i] = cpy_cmd(ptr, i);
		i++;
	}
	bingo->cmds[pipe] = NULL;
	bingo->tudo = malloc(3 * sizeof(char **));
	bingo->tudo[0] = bingo->cmds;
	bingo->tudo[2] = NULL;
}

/* Parse antigo pra não ter perigo de tudo dar errado
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
}*/
