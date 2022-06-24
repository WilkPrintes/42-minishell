/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:46:25 by lucferna          #+#    #+#             */
/*   Updated: 2022/06/24 22:30:39 by lucferna         ###   ########.fr       */
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

int	move_to_cmd(char *ptr, int cmd_nb)
{
	int	i;

	i = 0;
	while (ptr[i] != '\0' && cmd_nb != 0)
	{
		if (ptr[i++] == '|')
			cmd_nb--;
	}
	while (!ft_isalpha(ptr[i]))
		i++;
	return (i);
}

int	full_size(char *args, int cmd_nb)
{
	int	i;
	int	size;

	i = move_to_cmd(args, cmd_nb);
	size = 0;
	while (args[i] != '\0' && args[i] != '|' && args[i++] != ' ')
		size++;
	while (args[i] != '\0' && args[i] != '|')
	{
		if ((ft_isalnum(args[i]) || args[i] == '-') && args[i - 1] == ' ')
		{
			size++;
			while (args[i] != '\0' && args[i] != '|' && args[i] != ' ')
			{
				i++;
				size++;
			}
		}
		if (args[i] == '|' || args[i] == '\0')
			break ;
		i++;
	}
	return (size + 1);
}

void	add_args(char *cmd, char *ptr, int cmd_nb)
{
	int	i;
	int	j;

	j = 0;
	i = move_to_cmd(ptr, cmd_nb);
	while (cmd[j] != '\0')
		j++;
	while (ptr[i] != '\0' && ptr[i] != '|' && ptr[i] != ' ')
		i++;
	while (ptr[i] != '\0' && ptr[i] != '|')
	{
		if (ft_isalnum(ptr[i]) && ptr[i - 1] == ' ')
		{
			cmd[j++] = ' ';
			while (ptr[i] != '\0' && ptr[i] != '|' && ptr[i] != ' ')
				cmd[j++] = ptr[i++];
		}
		if (ptr[i] == '|' || ptr[i] == '\0')
			break ;
		i++;
	}
}

char	*cpy_cmd(char *ptr, int cmd_nb)
{
	int		i;
	int		j;
	char	*new;

	i = move_to_cmd(ptr, cmd_nb);
	j = 0;
	new = calloc(full_size(ptr, cmd_nb), sizeof(char));
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
	add_args(new, ptr, cmd_nb);
	return (new);
}

int	parse(char *ptr, t_main *bingo)
{
	int	pipe;
	int	i;

	if (have_quotes(ptr) == -1)
		return (write(2, "error\n", 6));
	fix_quotes(ptr);
	i = 0;
	pipe = number_of_commands(ptr);
	bingo->cmds = malloc((pipe + 1) * sizeof(char *));
	while (i != pipe)
	{
		bingo->cmds[i] = cpy_cmd(ptr, i);
		refix_quotes(bingo->cmds[i]);
		printf("%s\n", bingo->cmds[i]);
		i++;
	}
	bingo->cmds[pipe] = NULL ;
}
