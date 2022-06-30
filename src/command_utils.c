#include "minishell.h"

char	*find_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	paths = ft_split(getenv("PATH"), ':');
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

void	command(char *envp, char *ptr)
{
	int		i;
	int	j;
	char	*path;
	char	**cmd;

	i = 0;
	cmd = ft_split(ptr, ' ');
	while (cmd[i] != NULL)
	{
		if (have_quotes(cmd[i]) == 1)
			cmd[i] = remove_quotes(cmd[i], cmd[i][0]);
		refix_quotes(cmd[i++]);
	}
	path = find_path(cmd[0]);
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		free_matriz(&cmd);
		ft_putstr_fd(" command not found\n", 2);
		exit(127);
	}
	if (execve(path, cmd, NULL) == -1)
	{
		free_matriz(&cmd);
		free(path);
		error();
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
