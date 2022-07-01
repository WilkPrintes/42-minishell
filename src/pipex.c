/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:53:45 by wprintes          #+#    #+#             */
/*   Updated: 2022/06/23 12:47:58 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_command(char **argv, t_data *data);
void	second_command(char **argv, t_data *data);

int	pipex(char *argv[])
{
	t_data	data;

	if (pipe(data.fd) == -1)
		error();
	data.pid1 = fork();
	if (data.pid1 == -1)
		error();
	if (data.pid1 == 0)
		first_command(argv, &data);
	else
	{
		waitpid(data.pid1, NULL, 0);
		second_command(argv, &data);
	}
	return (0);
}

void	first_command(char **argv, t_data *data)
{
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	command(getenv("PATH"), argv[0]);
}

void	second_command(char **argv, t_data *data)
{
	dup2(data->fd[0], STDIN_FILENO);
	close(data->fd[1]);
	command(getenv("PATH"), argv[1]);
}
