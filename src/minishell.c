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

int	g_status;

int		equalexist(char *ptr);
int		find_pipes(char *ptr);

void	set_original_fd(int *original_fd)
{
	original_fd[0] = dup(STDIN_FILENO);
	original_fd[1] = dup(STDOUT_FILENO);
}

void	reset_original_fd(int *original_fd, int *dif_fd)
{
	if (dif_fd[0] != STDIN_FILENO)
		close(dif_fd[0]);
	if (dif_fd[1] != STDOUT_FILENO)
		close(dif_fd[1]);
	dup2(original_fd[0], STDIN_FILENO);
	dup2(original_fd[1], STDOUT_FILENO);
}

char	*call_rl(t_data_var *data)
{
	char	*ptr;

	ptr = readline("minishell: ");
	if (ptr == NULL)
		close_shell(NULL, ptr, data);
	add_history(ptr);
	return (ptr);
}

int	single_command(t_resources *resources, t_data_var *data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		command(data->contents[find_index(data, "PATH")], resources->cmds[0],
				data);
	else
		waitpid(pid, &g_status, 0);
	return (g_status);
}

int	multiple_commands(t_data_var *data, char **cmds, int pipes)
{
	int	pid;

	data->pipes = pipes;
	pid = fork();
	if (pid == 0)
		pipex(cmds, data);
	else
		waitpid(pid, &g_status, 0);
	return (g_status);
}

int	minishell(t_resources *resources, t_data_var *data)
{
	int		i_status;
	int		original_fd[2];

	set_original_fd(original_fd);
	i_status = data->i_status;
	g_status = 0;
	resources->cmds = parse(resources->line);
	if (resources->cmds == NULL)
		return (0);
	redirect(resources->line, data);
	if (number_of_commands(resources->line) > 0)
		multiple_commands(data, resources->cmds,
			number_of_commands(resources->line));
	else if (is_built_in(resources, resources->cmds) == 1)
		exec_built_in(resources->cmds, resources->line, data);
	else if (ft_strncmp(resources->line, "clear", 5) == 0)
		printf("\e[1;1H\e[2J");
	else if (equalexist(resources->line) != -1)
		var_func(resources->line, data);
	else
		single_command(resources, data);
	data->contents[i_status] = ft_itoa(g_status);
	reset_original_fd(original_fd, data->dif_fd);
	free_this(resources->cmds);
	free(resources->line);
	return (g_status);
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

void	init_args(t_data_var *data, char *envp[])
{
	signal(SIGINT, handi);
	signal(SIGQUIT, SIG_IGN);
	data->here_doc = -1;
	data->count_var = 0;
	data->names = ft_calloc(sizeof(char *), 1024);
	data->contents = ft_calloc(sizeof(char *), 1024);
	data->global = ft_calloc(sizeof(int), 1024);
	data->count_var = init_vars(data, envp);
	data->i_status = data->count_var - 1;
}

int	main(int argc, char **argv, char *envp[])
{
	t_data_var			data;
	t_resources			resources;
	int					status;
	char				*ptr;

	if (argc > 1)
	{
		ft_putstr_fd("Minishell doesn't take any arguments.\n", 2);
		return (1);
	}
	init_args(&data, envp);
	while (1)
	{
		resources.line = call_rl(&data);
		status = minishell(&resources, &data);
	}
	if (data.here_doc != -1)
	{
		close(data.here_doc);
		unlink(".temp_file");
	}
	return (status);
}
