/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:53:45 by wprintes          #+#    #+#             */
/*   Updated: 2022/07/13 17:27:00 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_command(char **argv, t_data *t_pipe, t_data_var *data);
void	second_command(char **argv, t_data *t_pipe, t_data_var *data);

int	pipex(char *argv[], t_data_var *data)
{
	t_data	t_pipe;

	if (pipe(t_pipe.fd) == -1)
		error();
	t_pipe.pid1 = fork();
	if (t_pipe.pid1 == -1)
		error();
	if (t_pipe.pid1 == 0)
		first_command(argv, &t_pipe, data);
	else
	{
		waitpid(t_pipe.pid1, NULL, 0);
		second_command(argv, &t_pipe, data);
	}
	return (0);
}

void	first_command(char **argv, t_data *t_pipe, t_data_var *data)
{
	dup2(t_pipe->fd[1], STDOUT_FILENO);
	close(t_pipe->fd[0]);
	command(getenv("PATH"), argv[0], data);
}

void	second_command(char **argv, t_data *t_pipe, t_data_var *data)
{
	dup2(t_pipe->fd[0], STDIN_FILENO);
	close(t_pipe->fd[1]);
	command(getenv("PATH"), argv[1], data);
}