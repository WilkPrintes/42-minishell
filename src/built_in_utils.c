/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lucas_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:46:21 by lucferna          #+#    #+#             */
/*   Updated: 2022/07/15 14:28:30 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**built_in_functions(void)
{
	char	**ptr;

	ptr = malloc(8 * sizeof(char *));
	ptr[0] = ft_strdup("cd");
	ptr[1] = ft_strdup("pwd");
	ptr[2] = ft_strdup("exit");
	ptr[3] = ft_strdup("echo");
	ptr[4] = ft_strdup("export");
	ptr[5] = ft_strdup("unset");
	ptr[6] = ft_strdup("env");
	ptr[7] = NULL;
	return (ptr);
}

int	is_built_in(char **built_in, char **cmds)
{
	int		i;
	int		n_cmds;
	char	**hold;

	n_cmds = 0;
	while (cmds[n_cmds] != NULL)
	{
		i = 0;
		hold = ft_split(cmds[n_cmds], ' ');
		while (i < 7)
		{
			if (ft_strncmp(built_in[i], hold[0], ft_strlen(hold[0])) == 0)
			{
				free_this(hold);
				return (1);
			}
			i++;
		}
		n_cmds++;
		free_this(hold);
	}
	return (0);
}

int	exec_built_in(char **cmds, char *ptr, t_data_var *data)
{
	int		i;
	char	teste[256];
	char	**hold;

	i = -1;
	while (cmds[++i] != NULL)
	{
		hold = ft_split(cmds[i], ' ');
		if (ft_strncmp(hold[0], "exit", ft_strlen(hold[0])) == 0)
			close_shell(cmds, ptr, data);
		else if (ft_strncmp(hold[0], "pwd", ft_strlen(hold[0])) == 0)
			printf("%s\n", getcwd(teste, sizeof(teste)));
		else if (ft_strncmp(hold[0], "cd", ft_strlen(hold[0])) == 0)
			chdir(hold[1]);
		else if (ft_strncmp(hold[0], "echo", ft_strlen(hold[0])) == 0)
			echo(hold, data);
		else if (ft_strncmp(hold[0], "export", ft_strlen(hold[0])) == 0)
			ft_export(data, hold);
		else if (ft_strncmp(hold[0], "unset", ft_strlen(hold[0])) == 0)
			unset(hold[1], data);
		else if (ft_strncmp(hold[0], "env", ft_strlen(hold[0])) == 0)
			env(data);
		free_this(hold);
	}
	return (0);
}

void	free_this(char **str)
{
	int	i;

	i = 0;
	if (str == 0)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}
