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

int	single_command(t_data_var *data, char *cmd)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == 0)
		command(data->contents[find_index(data, "PATH")], cmd, data);
	else
		waitpid(pid, &status, 0);
	return (status);
}

int	multiple_commands(t_data_var *data, char **cmds, int pipes)
{
	int	pid;
	int	status;

	status = 0;
	data->pipes = pipes;
	pid = fork();
	if (pid == 0)
		pipex(cmds, data);
	else
		waitpid(pid, &status, 0);
	return (status);
}

int	minishell(char **built_in, char *ptr, t_data_var *data)
{
	char	**cmds;
	int		i_status;
	int		status;
	int		original_fd[2];

	set_original_fd(original_fd);
	i_status = data->i_status;
	status = 0;
	cmds = parse(ptr);
	if (cmds == NULL)
		return (0);
	redirect(ptr, data);
	if (find_pipes(ptr) > 0)
		status = multiple_commands(data, cmds, number_of_commands(ptr));
	else if (is_built_in(built_in, cmds) == 1)
		status = exec_built_in(cmds, ptr, data);
	else if (ft_strncmp(ptr, "clear", 5) == 0)
		printf("\e[1;1H\e[2J");
	else if (equalexist(ptr) != -1)
		var_func(ptr, data);
	else
		status = single_command(data, cmds[0]);
	data->contents[i_status] = ft_itoa(status);
	reset_original_fd(original_fd, data->dif_fd);
	free_this(cmds);
	free(ptr);
	return (status);
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
	int					status;
	char				*ptr;
	char				**built_in;

	if (argc > 1)
	{
		ft_putstr_fd("Minishell doesn't take any arguments.\n", 2);
		return (1);
	}
	init_args(&data, envp);
	built_in = built_in_functions();
	while (1)
	{
		ptr = call_rl(&data);
		status = minishell(built_in, ptr, &data);
	}
	if (data.here_doc != -1)
	{
		close(data.here_doc);
		unlink(".temp_file");
	}
	free_this(built_in);
	return (status);
}
