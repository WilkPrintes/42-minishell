/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:24:38 by wprintes          #+#    #+#             */
/*   Updated: 2022/07/15 21:00:12 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_caracter(char *ptr, char caracter)
{
	int	ptr_len;
	int	i;

	ptr_len = ft_strlen(ptr);
	i = 0;
	while (i < ptr_len)
	{
		if (ptr[i] == caracter)
			return (i);
		i++;
	}
	return (-1);
}

int	init_vars(t_data_var *data, char *envp[])
{
	int	len;
	int	char_p;
	int	envp_len;

	len = 0;
	char_p = 0;
	while (envp[len] != NULL)
	{
		char_p = find_caracter(envp[len], '=');
		envp_len = strlen(envp[len]);
		data->names[len] = ft_substr(envp[len], 0, char_p);
		data->contents[len] = ft_substr(envp[len], char_p + 1, envp_len);
		data->global[len] = 1;
		len++;
	}
	data->names[len] = ft_strdup("?");
	data->contents[len] = ft_strdup("0");
	data->global[len] = 0;
	len++;
	return (len);
}

void	remake_quoted(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		if (have_quotes(ptr[i]) == 1)
			ptr[i] = remove_quotes(ptr[i]);
		refix_quotes(ptr[i++]);
	}
}
