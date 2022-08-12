/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:41:00 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/12 02:10:29 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_to_str(char **cmd, t_data_var *data);

char	*find_path(char *cmd, char *envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	if (!envp)
		return (NULL);
	paths = ft_split(envp, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_matriz(&paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_matriz(&paths);
	return (NULL);
}

void	command(char *envp, char *ptr, t_data_var *data, t_resources *re)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(ptr, ' ');
	remake_quoted(cmd);
	if (is_built_in(re, cmd) == 1)
	{
		exec_built_in(cmd, ptr, data);
		exit(0);
	}
	path = find_path(cmd[0], envp);
	if (!path)
	{
		if (access(cmd[0], X_OK) != -1)
			path = ft_strdup(cmd[0]);
		else
		{
			printf("%s: command not found\n", cmd[0]);
			free_matriz(&cmd);
			exit(127);
		}
	}
	var_to_str(cmd, data);
	if (execve(path, cmd, NULL) == -1)
		free_error(&cmd, &path);
}

void	var_to_str(char **cmd, t_data_var *data)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '$')
		{
			index = find_index(data, cmd[i] + 1);
			free(cmd[i]);
			cmd[i] = ft_strdup(data->contents[index]);
		}
		i++;
	}
}

void	free_matriz(char ***buffer)
{
	int	i;

	i = 0;
	if (!*buffer)
		return ;
	while (*(*buffer + i))
		free(*(*buffer + i++));
	free(*buffer);
	*buffer = NULL;
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
	while (!ft_isargument(ptr[i]))
		i++;
	return (i);
}
