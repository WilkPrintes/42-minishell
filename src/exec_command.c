/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:03:39 by lucferna          #+#    #+#             */
/*   Updated: 2022/08/14 22:21:30 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*call_rl(t_data_var *data)
{
	char	*ptr;
	int		len;

	len = 0;
	ptr = readline("\001\033[0;32mminishell@42sp\033[0m: $ ");
	if (ptr == NULL)
	{
		while (len < MAX_VAR)
		{
			free((data->names)[len]);
			free((data->contents)[len]);
			len++;
		}
		free(data->global);
		free(data->contents);
		free(data->names);
		write(2, "exit\n", 5);
		exit (139);
	}
	add_history(ptr);
	return (ptr);
}

int	equalexist(char *ptr)
{
	if (find_caracter(ptr, ' ') != -1)
		return (-1);
	return (find_caracter(ptr, '='));
}

void	init_args(t_data_var *data, char *envp[])
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	data->here_doc = -1;
	data->count_var = 0;
	data->names = ft_calloc(sizeof(char *), MAX_VAR);
	data->contents = ft_calloc(sizeof(char *), MAX_VAR);
	data->global = ft_calloc(sizeof(int), MAX_VAR);
	data->count_var = init_vars(data, envp);
	data->i_status = data->count_var - 1;
	data->exit = 0;
}

void	free_error(char ***ptr, char **path)
{
	free_matriz(ptr);
	free(path[0]);
	error();
}
