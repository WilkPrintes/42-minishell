/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:24:38 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/13 03:28:56 by lucferna         ###   ########.fr       */
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
	long	len;
	int		char_p;
	int		envp_len;
	int		data_i;

	len = 0;
	data_i = 0;
	char_p = 0;
	while (envp[len] != NULL)
	{
		if (is_env(envp[len]) == 0)
		{
			char_p = find_caracter(envp[len], '=');
			envp_len = strlen(envp[len]);
			data->names[data_i] = ft_substr(envp[len], 0, char_p);
			data->contents[data_i] = ft_substr(envp[len], char_p + 1, envp_len);
			data->global[data_i] = 1;
			data_i++;
		}
		len++;
	}
	data->names[data_i] = ft_strdup("?");
	data->contents[data_i] = ft_strdup("0");
	data->global[data_i++] = 0;
	return (data_i);
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

int	free_this(char **str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i])
		free(str[i++]);
	free(str);
	return (0);
}

int	ft_isargument(int c)
{
	if (ft_isalnum(c) == 1 || c == 39 || c == 34 || c == 46 || c == '$'
		|| c == '/' || c == '+' || c == '-' || c == '*' || c == '!')
		return (1);
	else
		return (0);
}
