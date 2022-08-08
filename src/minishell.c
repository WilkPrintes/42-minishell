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

int	single_command(t_resources *re, t_data_var *data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		command(data->contents[find_index(data, "PATH")], re->cmds[0], data,
			re);
	else
		waitpid(pid, &g_status, 0);
	return (g_status);
}

int	multiple_commands(t_data_var *data, t_resources *re, int pipes)
{
	int	pid;

	data->pipes = pipes;
	pid = fork();
	if (pid == 0)
		pipex(re->cmds, data, re);
	else
		waitpid(pid, &g_status, 0);
	return (g_status);
}

void	minishell(t_resources *re, t_data_var *data)
{
	int		i_status;
	int		original_fd[2];

	set_original_fd(original_fd);
	i_status = data->i_status;
	g_status = 0;
	re->cmds = parse(re->line);
	if (re->cmds == NULL)
		return (free(re->line));
	redirect(re->line, data);
	if (number_of_commands(re->line) > 0)
		multiple_commands(data, re, number_of_commands(re->line));
	else if (is_built_in(re, re->cmds) == 1)
		g_status = exec_built_in(re->cmds, re->line, data);
	else if (ft_strncmp(re->line, "clear", biggest("clear", re->line)) == 0)
		printf("\e[1;1H\e[2J");
	else if (equalexist(re->line) != -1)
		var_func(re->line, data);
	else
		single_command(re, data);
	free(data->contents[i_status]);
	data->contents[i_status] = ft_itoa(g_status);
	reset_original_fd(original_fd, data->dif_fd);
	free_this(re->cmds);
	free(re->line);
}

void	init_args(t_data_var *data, char *envp[])
{
	signal(SIGINT, handle_sigint);
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
		minishell(&resources, &data);
	}
	if (data.here_doc != -1)
	{
		close(data.here_doc);
		unlink(".temp_file");
	}
	return (g_status);
}
