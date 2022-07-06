/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lucas_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:46:21 by lucferna          #+#    #+#             */
/*   Updated: 2022/07/01 20:44:28 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**built_in_functions(void)
{
	char	**ptr;

	ptr = malloc(3 * sizeof(char *));
	ptr[0] = ft_strdup("cd");
	ptr[1] = ft_strdup("pwd");
	ptr[2] = ft_strdup("exit");
	return (ptr);
}

int	is_built_in(char **fts, char *str)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_strncmp(fts[i], str, ft_strlen(fts[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	close_shell(char *ptr)
{
	free(ptr);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int	exec_built_in(char *ptr)
{
	char	teste[256];

	if (ft_strncmp(ptr, "exit", 4) == 0)
		close_shell(ptr);
	else if (ft_strncmp(ptr, "pwd", 3) == 0)
	{
		getcwd(teste, sizeof(teste));
			printf("%s\n", teste);
	}
	else if (ft_strncmp(ptr, "cd", 2) == 0)
	{
		chdir(ptr + 3);
		getcwd(teste, sizeof(teste));
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
