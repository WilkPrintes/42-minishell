/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:03:39 by lucferna          #+#    #+#             */
/*   Updated: 2022/07/15 21:47:39 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*call_rl(t_data_var *data)
{
	char	*ptr;

	ptr = readline("minishell: ");
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
