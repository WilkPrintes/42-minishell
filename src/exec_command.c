/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:03:39 by lucferna          #+#    #+#             */
/*   Updated: 2022/08/08 00:43:45 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*call_rl(t_data_var *data)
{
	char	*ptr;

	ptr = readline("\033[0;32mminishell@42sp\033[0m: $ ");
	if (ptr == NULL)
		close_shell(NULL, NULL, ptr, data);
	add_history(ptr);
	return (ptr);
}

int	equalexist(char *ptr)
{
	if (find_caracter(ptr, ' ') != -1)
		return (-1);
	return (find_caracter(ptr, '='));
}

void	handle_sigint(int signum)
{
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	return ;
}

void	free_error(char ***ptr, char **path)
{
	free_matriz(ptr);
	free(path[0]);
	error();
}
