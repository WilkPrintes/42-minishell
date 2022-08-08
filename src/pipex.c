/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:53:45 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/08 00:33:10 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_command(char *argv, t_data *t_pipe, t_data_var *data,
			t_resources *re);
void	second_command(char *argv, t_data *t_pipe, t_data_var *data,
			t_resources *re);

int	pipex(char *argv[], t_data_var *data, t_resources *re)
{
	t_data	t_pipe;
	int		i;

	i = 0;
	t_pipe.temp_fd = STDIN_FILENO;
	while (i < data->pipes)
	{
		if (pipe(t_pipe.fd) == -1)
			error();
		t_pipe.pid1 = fork();
		if (t_pipe.pid1 == -1)
			error();
		if (t_pipe.pid1 == 0)
			first_command(argv[i], &t_pipe, data, re);
		else
		{
			waitpid(t_pipe.pid1, NULL, 0);
			close(t_pipe.fd[1]);
			close(t_pipe.temp_fd);
			t_pipe.temp_fd = dup(t_pipe.fd[0]);
		}
		i++;
	}
	second_command(argv[i], &t_pipe, data, re);
	return (0);
}

void	first_command(char *argv, t_data *t_pipe, t_data_var *data,
					t_resources *re)
{
	dup2(t_pipe->fd[1], STDOUT_FILENO);
	dup2(t_pipe->temp_fd, STDIN_FILENO);
	close(t_pipe->fd[0]);
	command(getenv("PATH"), argv, data, re);
}

void	second_command(char *argv, t_data *t_pipe, t_data_var *data,
					t_resources *re)
{
	dup2(t_pipe->temp_fd, STDIN_FILENO);
	close(t_pipe->fd[0]);
	close(t_pipe->fd[1]);
	command(getenv("PATH"), argv, data, re);
}
