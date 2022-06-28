/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:15:27 by wprintes          #+#    #+#             */
/*   Updated: 2022/05/28 16:15:27 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int		equalexist(char *ptr);
int		find_pipes(char *ptr);

t_main	ito;

void	func_doida(/* char **inate,  */t_data_var *data)
{
	char	*ptr;
	int		pid;
	char	pwd[256];

	ptr = readline("minishell: ");
	if (ptr == NULL)
		close_shell(ptr);
	add_history(ptr);
	parse(ptr, &ito);
	if (find_pipes(ptr) == 1)
	{
		pid = fork();
		if (pid == 0)
			pipex(ito.cmds);
		else
			waitpid(pid, NULL, 0);
	}
/* 	else if (is_built_in(inate, ptr) == 1)
		exec_built_in(ptr); */
	else if (ft_strncmp(ptr, "clear", 5) == 0)
		printf("\e[1;1H\e[2J");
	else if (equalexist(ptr) != -1)
		var_func(ptr, data);
	else if (ft_strncmp(ptr, "echo", 4) == 0)
		echo(ptr, data);
	else if (ft_strncmp(ptr, "unset", 5) == 0)
		unset(ptr, data);
	free_this(ito.cmds);
	free(ptr);
}

int find_pipes(char *ptr)
{
	int len;

	len = 0;
	while(ptr[len] != '\0')
	{
		if (ptr[len] == '|')
			return (1);
		len++;
	}
	return (0);
}

int	equalexist(char *ptr)
{
	if (find_caracter(ptr, ' ') != -1)
		return (-1);
	return (find_caracter(ptr, '='));
}

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

void	handi(int signum)
{
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

int	main(void)
{
/* 	char				**inate;
	struct sigaction	sa; */
	t_data_var			data;

/* 	sa.sa_handler = handi;
	inate = built_in_functions(); */
	signal(SIGINT, handi);
	signal(SIGQUIT, SIG_IGN);
	data.count_var = 0;
	data.names = malloc(sizeof(char *) * 1024);
	data.contents = malloc(sizeof(char *) * 1024);
	while (1)
		func_doida(/* inate,  */&data);
}

