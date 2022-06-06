/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lucas_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:46:21 by lucferna          #+#    #+#             */
/*   Updated: 2022/06/06 19:48:47 by lucferna         ###   ########.fr       */
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
	{	//Mudar strlen para tamanho certo após parsing
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
		getcwd(teste, sizeof(teste)); // Pega atual diretório e coloca no buffer
			printf("%s\n", teste);
	}
	else if (ft_strncmp(ptr, "cd", 2) == 0)
	{
		chdir(ptr + 3);
		getcwd(teste, sizeof(teste)); // Pega atual diretório e coloca no buffer
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

int	have_quotes(char *ptr)
{
	int	val;
	int	i;

	val = 0;
	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 || ptr[i] == 39)
			val++;
		i++;
	}
	if (val % 2 != 0)
		return (-1);
	else if (val == 0)
		return (0);
	return (1);
}

void	fix_quotes(char *ptr)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 && trigger == 0)
			trigger = 34;
		else if (ptr[i] == 39 && trigger == 0)
			trigger = 39;
		else if (trigger != 0 && ptr[i] == 32)
			ptr[i] = 7;
		else if (ptr[i] == trigger)
			trigger = 0;
		i++;
	}
}

void	refix_quotes(char *ptr)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 && trigger == 0)
			trigger = 34;
		else if (ptr[i] == 39 && trigger == 0)
			trigger = 39;
		else if (trigger != 0 && ptr[i] == 7)
			ptr[i] = ' ';
		else if (ptr[i] == trigger)
			trigger = 0;
		i++;
	}
}
