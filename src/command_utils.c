/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:41:00 by wprintes          #+#    #+#             */
/*   Updated: 2022/07/18 21:24:10 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		i;
	char	*path;
	char	**cmd;

	i = 0;
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
		ft_putstr_fd(cmd[0], 2);
		free_matriz(&cmd);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	else if (execve(path, cmd, NULL) == -1)
		free_error(&cmd, &path);
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

void	error(void)
{
	perror("Error");
	exit (EXIT_FAILURE);
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
