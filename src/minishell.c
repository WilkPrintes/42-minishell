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

int		equalexist(char *ptr);
int		find_pipes(char *ptr);

t_main	g_ito;

void	func_doida(t_data_var *data)
{
	char	*ptr;
	int		pid;
	char	pwd[256];
	int		i_status;
	int		status;

	i_status = data->i_status;
	status = 0;
	ptr = readline("minishell: ");
	if (ptr == NULL)
		close_shell(ptr);
	add_history(ptr);
	parse(ptr, &g_ito);
	if (find_pipes(ptr) == 1)
	{
		pid = fork();
		if (pid == 0)
			pipex(g_ito.cmds);
		else
			waitpid(pid, &status, 0);
	}
	else if (ft_strncmp(ptr, "clear", 5) == 0)
		printf("\e[1;1H\e[2J");
	else if (equalexist(ptr) != -1)
		var_func(ptr, data);
	else if (ft_strncmp(ptr, "echo", 4) == 0)
		echo(ptr, data);
	else if (ft_strncmp(ptr, "unset", 5) == 0)
		unset(ptr, data);
	else if (ft_strncmp(ptr, "env", 3) == 0)
		env(data);
	else if (ft_strncmp(ptr, "export", 6) == 0)
		ft_export(data, ptr);
	else if (*ptr)
	{
		pid = fork();
		if (pid == 0)
			command(data->contents[find_index(data, "PATH")], ptr);
		else
			waitpid(pid, &status, 0);
	}
	data->contents[i_status] = ft_itoa(status);
	free_this(g_ito.cmds);
	free(ptr);
}

int	find_pipes(char *ptr)
{
	int	len;

	len = 0;
	while (ptr[len] != '\0')
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

void	handi(int signum)
{
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char *envp[])
{
	t_data_var			data;

	signal(SIGINT, &handi);
	signal(SIGQUIT, SIG_IGN);
	data.count_var = 0;
	data.names = malloc(sizeof(char *) * 1024);
	data.contents = malloc(sizeof(char *) * 1024);
	data.global = malloc(sizeof(int *) * 1024);
	data.count_var = init_vars(&data, envp);
	data.i_status = data.count_var - 1;
	int pid;
	while (1)
		func_doida(&data);
}
