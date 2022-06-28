/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:15:16 by wprintes          #+#    #+#             */
/*   Updated: 2022/05/28 16:15:16 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_func(char *ptr, t_data_var *data) //coloca as varíaveis no data_vars
{
	int		p;
	int		i;
	int		len;
	int		exists;
	char	*name;

	i = data->count_var;
	p = find_caracter(ptr, '=');
	len = ft_strlen(ptr);
	name = ft_substr(ptr, 0, p);
	exists = var_exists(data, name);
	if (i > 0 && exists != -1) //verifica se a varíavel já existe
	{
		free(data->contents[exists]);
		data->contents[exists] = ft_substr(ptr, p + 1, len);
	}
	else
	{
		data->names[i] = ft_strdup(name);
		data->contents[i] = ft_substr(ptr, p + 1, len);
		data->global[i] = 0;
		data->count_var++;
	}
	free(name);
}


int find_content(t_data_var *data, char *ptr, int i)
{
	char	*name;
	int		len;
	int		exists;

	len = find_caracter(ptr + i, ' ');
	if (len == -1)
		len = ft_strlen(ptr) - i;
	len = len - 1;
	name = ft_substr(ptr, i + 1, len);
	exists = var_exists(data, name);
	if (exists != -1)
		printf("%s", data->contents[exists]);
	len = ft_strlen(name);
	free(name);
	return (len);
}

int find_index(t_data_var *data, char *ptr)
{
	int i;
	char *temp;
	int	len;

	i = 0;	
	while(i < data->count_var)
	{
		temp = ft_strdup(data->names[i]);
		len = ft_strlen(data->names[i]);
		if (ft_strncmp(data->names[i], ptr, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int var_exists(t_data_var *data, char *name)
{
	int i;

	i = 0;
	while (i < data->count_var)
	{
		if (ft_strlen(name) == ft_strlen(data->names[i]))
		{
			if (ft_strncmp(name, data->names[i], ft_strlen(name)) == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}
