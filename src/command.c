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

void	echo(char *ptr, t_data_var *data)
{
	int	len;
	int	i;
	int	path;

	path = find_index(data, "PATH");
	if (!data->contents[path])
	{
		printf("echo: command not found\n");
		return ;
	}
	len = ft_strlen(ptr);
	if (ft_strncmp(ptr, "echo -n", 7) == 0)
		i = 8;
	else
		i = 5;
	while (i < len)
	{
		if (ptr[i] != '$')
			printf("%c", ptr[i]);
		else
			i = i + find_content(data, ptr, i);
		i++;
	}
	if (ft_strncmp(ptr + 5, "-n", 2) != 0)
		printf("\n");
}

void	unset(char *ptr, t_data_var *data)
{
	int	index;

	index = find_index(data, ptr + 6);
	if (index != -1)
		data->contents[index] = NULL;
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

void	ft_export(t_data_var *data, char *name)
{
	char	*temp;
	int		index;

	temp = ft_substr(name, 7, ft_strlen(name));
	index = find_index(data, temp);
	free(temp);
	if (index != -1)
		data->global[index] = 1;
}
