/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:24:38 by wprintes          #+#    #+#             */
/*   Updated: 2022/07/14 03:09:39 by wprintes         ###   ########.fr       */
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

void	set_dir(char **cd, char *pwd)
{
	char	*minishell;
	char	*temp;
	char	*color;
	char	*pwd_temp;
	
	pwd_temp = pwd;
	minishell = ft_strdup("\033[1;32mminishell@42\e[0m:\033[0;36m");
	if (ft_strncmp(pwd, "/home/", 6) == 0)
		remove_dir(&pwd_temp);
	color = ft_strjoin(pwd_temp, "\e[0m");
	temp = ft_strjoin(minishell, color);
	cd[0] = ft_strjoin(temp, "$ ");
	free(minishell);
	free(temp);
	free(pwd_temp);
	free(color);
}

void	remove_dir(char **pwd)
{
	int		i;
	int		len;
	int		count;
	char	*temp;
	char	*result;

	// temp = ft_strdup(getenv("PWD"));
	temp = getenv("PWD");
	i = 0;
	count = 0;
	len = ft_strlen(temp);
	while (i < len - 1)
	{
		if (temp[i] == '/')
			count++;
		if (count == 3)
			break ;
		i++;
	}
	result = ft_substr(pwd[0], i, ft_strlen(pwd[0]));
	pwd[0] = ft_strjoin("~", result);
	free(result);
}
