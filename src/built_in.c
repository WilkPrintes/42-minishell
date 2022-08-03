/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:15:32 by wprintes          #+#    #+#             */
/*   Updated: 2022/05/28 16:15:32 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **echo, t_data_var *data)
{
	int	i;

	i = 1;
	while (echo[i] != NULL)
	{
		refix_quotes(echo[i]);
		if (!print_echo(echo[i], data) && echo[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	remake_quoted(echo);
	if (echo[1] != NULL && ft_strncmp(echo[1], "-n", 2) != 0)
		printf("\n");
}

void	unset(char *ptr, t_data_var *data)
{
	int	index;

	index = find_index(data, ptr);
	if (index != -1)
	{
		data->contents[index] = NULL;
		data->global[index] = 0;
	}
}

void	env(t_data_var *data)
{
	int	i;
	int	path;

	path = find_index(data, "PATH");
	i = 0;
	if (!data->contents[path])
	{
		printf("env: command not found\n");
		return ;
	}
	while (i < data->count_var)
	{
		if (data->global[i] == 1)
		{
			printf("%s=", data->names[i]);
			printf("%s\n", data->contents[i]);
		}
		i++;
	}
}

void	ft_export(t_data_var *data, char **name)
{
	char	*temp;
	int		index;

	temp = name[1];
	index = find_index(data, temp);
	if (index != -1)
		data->global[index] = 1;
}

void	close_shell(char **extra, char **cmds, char *ptr, t_data_var *data)
{
	int	len;
	long status;

	if (extra[1])
		status = ft_atoi(extra[1]);
	len = 0;
	while (len < 1024)
	{
		free((data->names)[len]);
		free((data->contents)[len]);
		len++;
	}
	free(data->global);
	free(data->contents);
	free(data->names);
	free(ptr);
	free_this(cmds);
	free_this(extra);
	printf("exit\n");
	exit(status);
}
