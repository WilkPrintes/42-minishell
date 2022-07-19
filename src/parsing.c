/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:46:25 by lucferna          #+#    #+#             */
/*   Updated: 2022/07/19 23:46:48 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isargument(int c)
{
	if (ft_isalnum(c) == 1 || c == 39 || c == 34 || c == 250 || c == '$')
		return (1);
	else
		return (0);
}

static int	full_size(char *args, int cmd_nb)
{
	int	i;
	int	size;

	i = move_to_cmd(args, cmd_nb);
	size = 0;
	while (args[i] != '\0' && args[i] != '|' && args[i++] != ' ')
		size++;
	while (args[i] != '\0' && args[i] != '|')
	{
		if ((ft_isargument(args[i]) || args[i] == '-') && args[i - 1] == ' ')
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

static void	add_args(char *cmd, char *ptr, int cmd_nb)
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
		if (ptr[i] == '<' || ptr[i] == '>')
			break ;
		if (ft_isargument(ptr[i]) && ptr[i - 1] == ' ')
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

static char	*cpy_cmd(char *ptr, int cmd_nb)
{
	int		i;
	int		j;
	char	*new;

	i = move_to_cmd(ptr, cmd_nb);
	j = 0;
	new = calloc(full_size(ptr, cmd_nb), sizeof(char));
	while (ptr[i] != '\0' && ptr[i] != '|' && ptr[i] != ' ')
		new[j++] = ptr[i++];
	while (ptr[i - 1] != '\0' && ptr[i] != '|' && ptr[i] != 0)
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

int	go_to_command(char *ptr)
{
	int	i;
	int	moves;

	i = 0;
	if (ptr[0] == '>' || ptr[0] == '<')
	{
		while (ptr[i] != '\0' && ptr[i] != ' ')
			i++;
		while (ptr[i] != '\0' && ptr[i] == ' ')
			i++;
		while (ptr[i] != '\0' && ptr[i] != ' ')
			i++;
	}
	return (i);
}

char	**parse(char *ptr)
{
	int		pipe;
	int		i;
	char	**cmds;

	if (ptr[0] == '\0')
		return (NULL);
	if (have_quotes(ptr) == -1)
	{
		ft_putstr_fd("Error! Quotes should be closed.\n", 2);
		return (NULL);
	}
	fix_quotes(ptr);
	i = 0;
	ptr = ptr + go_to_command(ptr);
	pipe = number_of_commands(ptr) + 1;
	if (*ptr == '\0')
		return (NULL);
	cmds = malloc((pipe + 1) * sizeof(char *));
	while (i != pipe)
	{
		cmds[i] = cpy_cmd(ptr, i);
		i++;
	}
	cmds[pipe] = NULL;
	return (cmds);
}
