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

t_data_var			g_data;

int		equalexist(char *ptr);
int		find_pipes(char *ptr);

int	single_command(t_resources *re, t_data_var *data)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == 0)
		command(data->contents[find_index(data, "PATH")], re->cmds[0], data,
			re);
	else
		waitpid(pid, &status, 0);
	data->exit = WEXITSTATUS(status);
	return (data->exit);
}

int	multiple_commands(t_data_var *data, t_resources *re, int pipes)
{
	int	pid;
	int	status;

	status = 0;
	data->pipes = pipes;
	pid = fork();
	if (pid == 0)
		pipex(re->cmds, data, re);
	else
		waitpid(pid, &status, 0);
	return (data->exit);
}

void	minishell(t_resources *re, t_data_var *data)
{
	int		i_status;
	int		original_fd[2];

	set_original_fd(original_fd);
	i_status = data->i_status;
	re->cmds = parse(re->line);
	if (re->cmds == NULL)
		return (free(re->line));
	redirect(re->line, data);
	if (number_of_commands(re->line) > 0)
		data->exit = multiple_commands(data, re, number_of_commands(re->line));
	else if (is_built_in(re, re->cmds) == 1)
		data->exit = exec_built_in(re->cmds, re->line, data);
	else if (ft_strncmp(re->line, "clear", biggest("clear", re->line)) == 0)
		printf("\e[1;1H\e[2J");
	else if (equalexist(re->line) != -1)
		data->exit = var_func(re->line, data);
	else if (re->cmds[0] != NULL)
		data->exit = single_command(re, data);
	free(data->contents[i_status]);
	data->contents[i_status] = ft_itoa(data->exit);
	reset_original_fd(original_fd, data->dif_fd);
	free_this(re->cmds);
	free(re->line);
}

void	handle_sigint(int signum)
{
	signum = 2;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_data.exit = 137;
	return ;
}

int	main(int argc, char **argv __attribute__((unused)), char *envp[])
{
	t_resources			resources;

	if (argc > 1)
	{
		ft_putstr_fd("Minishell doesn't take any arguments.\n", 2);
		argv = NULL;
		return (1);
	}
	init_args(&g_data, envp);
	while (1)
	{
		resources.line = call_rl(&g_data);
		minishell(&resources, &g_data);
	}
	return (0);
}
