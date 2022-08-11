/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 00:39:27 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/12 00:12:17 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_cd(char **hold);

long	exit_erros(char **extra, char **cmds, char *ptr, t_data_var *data)
{
	long	status;

	status = 0;
	if (extra[1])
		status = ft_atoi(extra[1]);
	else
		status = ft_atoi(data->contents[data->i_status]);
	if (extra[1] && status == 0 && ft_strncmp(extra[1], "0", 1) != 0)
	{
		printf("exit\n");
		ft_putstr_fd(" numeric argument required\n", 2);
		exit_clean(extra, cmds, ptr, data);
		exit(2);
	}
	else if (extra[1])
	{
		if (extra[2])
		{
			printf("exit\n");
			ft_putstr_fd(" too many arguments\n", 2);
			exit_clean(extra, cmds, ptr, data);
			exit(1);
		}
	}
	return (status);
}

void	exit_clean(char **extra, char **cmds, char *ptr, t_data_var *data)
{
	int	len;

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
}

int	cd(char **hold, t_data_var *data)
{
	int	index;

	index = 0;
	if (hold[1] && hold[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (!hold[1])
	{
		index = find_index(data, "USER");
		free(hold[1]);
		hold[1] = ft_strdup(ft_strjoin("/home/", data->contents[index]));
	}
	if (ft_strncmp(hold[1], "$", 1) == 0)
	{
		index = find_index(data, hold[1] + 1);
		free(hold[1]);
		hold[1] = ft_strdup(data->contents[index]);
	}
	if (chdir(hold[1]) == -1)
		return (error_cd(hold));
	return (0);
}

int	error_cd(char **hold)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(hold[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}
