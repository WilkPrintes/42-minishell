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


void	func_doida(char **built_in, t_data_var *data)
{
	char	**cmds;
	char	*ptr;
	int		pid;
	int		i_status;
	int		status;

	i_status = data->i_status;
	status = 0;
	ptr = readline("minishell_teste: ");
	if (ptr == NULL)
		close_shell(NULL, ptr, data);
	cmds = parse(ptr);
	if (cmds == NULL)
		return ;
	redirect(ptr);
	add_history(ptr);
	if (find_pipes(ptr) > 0)
	{
		data->pipes = find_pipes(ptr);
		pid = fork();
		if (pid == 0)
			pipex(cmds, data);
		else
			waitpid(pid, &status, 0);
	}
	else if (is_built_in(built_in, cmds) == 1)
		status = exec_built_in(cmds, ptr, data);
	else if (ft_strncmp(ptr, "clear", 5) == 0)
		printf("\e[1;1H\e[2J");
	else if (equalexist(ptr) != -1)
		var_func(ptr, data);
	else
	{
		pid = fork();
		if (pid == 0)
			command(data->contents[find_index(data, "PATH")], cmds[0], data);
		else
			waitpid(pid, &status, 0);
	}
	dup2(data->temp_stdout, 1);
	dup2(data->temp_stdin, 0);
	data->contents[i_status] = ft_itoa(status);
	free_this(cmds);
	free(ptr);
}

int	find_pipes(char *ptr)
{
	int	len;
	int	result;

	result = 0;
	len = 0;
	while (ptr[len] != '\0')
	{
		if (ptr[len] == '|')
			result++;
		len++;
	}
	return (result);
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
 	rl_replace_line("", 1);
	rl_redisplay();
	return ;
}

int	main(int argc, char **argv, char *envp[])
{
	char				**built_in;
	t_data_var			data;

	built_in = built_in_functions();
	signal(SIGINT, handi);
	signal(SIGQUIT, SIG_IGN);
	data.count_var = 0;
	data.names = ft_calloc(sizeof(char *), 1024);
	data.contents = ft_calloc(sizeof(char *), 1024);
	data.global = ft_calloc(sizeof(int), 1024);
	data.count_var = init_vars(&data, envp);
	data.i_status = data.count_var - 1;
	while (1)
		func_doida(built_in, &data);
	free_this(built_in);
	return (0);
}
