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
    char *path;
    char **cmd;

	cmd = ft_split(ptr, ' ');
	path = find_path(cmd[0]);
    if (!path)
	{
		free_matriz(&cmd);
		ft_putstr_fd("command not found\n", 2);
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