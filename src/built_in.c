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

	if (!ptr)
		return ;
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
	int		v_index;

	temp = name[1];
	v_index = find_caracter(temp, '=');
	if (v_index != -1)
		var_func(temp, data);
	index = find_index(data, temp);
	if (index != -1)
		data->global[index] = 1;
}

int	close_shell(char **extra, char **cmds, char *ptr, t_data_var *data)
{
	long	status;

	status = exit_erros(extra, cmds, ptr, data);
	printf("exit\n");
	if (status != 0 || status != ft_atoi(extra[1]))
		exit_clean(extra, cmds, ptr, data);
	exit(status);
}
