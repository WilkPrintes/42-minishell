/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:46:21 by lucferna          #+#    #+#             */
/*   Updated: 2022/08/14 20:19:42 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**built_in_functions(void)
{
	char	**ptr;

	ptr = malloc(8 * sizeof(char *));
	ptr[0] = ft_strdup("cd");
	ptr[1] = ft_strdup("pwd");
	ptr[2] = ft_strdup("exit");
	ptr[3] = ft_strdup("echo");
	ptr[4] = ft_strdup("export");
	ptr[5] = ft_strdup("unset");
	ptr[6] = ft_strdup("env");
	ptr[7] = NULL;
	return (ptr);
}

int	is_built_in(t_resources *re, char **cmds)
{
	int		i;
	int		n_cmds;
	char	**hold;

	n_cmds = 0;
	re->built_in = built_in_functions();
	while (cmds[n_cmds] != NULL)
	{
		i = 0;
		hold = ft_split(cmds[n_cmds], ' ');
		while (i < 7)
		{
			if (ft_strncmp(re->built_in[i], hold[0], biggest(hold[0],
						re->built_in[i])) == 0)
			{
				free_this(hold);
				free_this(re->built_in);
				return (1);
			}
			i++;
		}
		n_cmds++;
		free_this(hold);
	}
	return (free_this(re->built_in));
}

int	exec_built_in(char **cmds, char *ptr, t_data_var *data)
{
	int		i;
	char	**hold;

	i = -1;
	while (cmds[++i] != NULL)
	{
		hold = ft_split(cmds[i], ' ');
		if (ft_strncmp(hold[0], "exit", biggest("exit", hold[0])) == 0)
			close_shell(hold, cmds, ptr, data);
		else if (ft_strncmp(hold[0], "pwd", biggest("pwd", hold[0])) == 0)
			exec_pwd();
		else if (ft_strncmp(hold[0], "cd", biggest("cd", hold[0])) == 0)
			data->exit = cd(hold, data);
		else if (ft_strncmp(hold[0], "echo", biggest("echo", hold[0])) == 0)
			data->exit = echo(hold, data);
		else if (ft_strncmp(hold[0], "export", biggest("export", hold[0])) == 0)
			ft_export(data, hold);
		else if (ft_strncmp(hold[0], "unset", biggest("unset", hold[0])) == 0)
			unset(hold, data);
		else if (ft_strncmp(hold[0], "env", biggest("env", hold[0])) == 0)
			env(data);
		free_this(hold);
	}
	return (data->exit);
}

static int	print_variable(char *str, t_data_var *data)
{
	int		i;
	int		j;
	int		len;
	char	*var;

	j = 0;
	len = 0;
	while (str[j] != '\0' && str[j] != ' ' && str[j] != 39)
	{
		len++;
		j++;
	}
	if (str[ft_strlen(str) - 1] == 34)
		str[ft_strlen(str) - 1] = '\0';
	var = ft_substr(str, 0, len);
	if (var_exists(data, var) != -1)
	{
		i = find_index(data, var);
		if (data->contents[i])
			ft_putstr_fd(data->contents[i], 1);
	}
	free(var);
	return (j);
}

int	print_echo(char *str, t_data_var *data)
{
	int		i;
	int		quote;
	char	*status;

	i = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			status = ft_itoa(data->exit);
			ft_putstr_fd(status, 1);
			free(status);
			i++;
		}
		else if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != ' '
			&& str[ft_strlen(str) - 1] != 39 && str[i + 1] != 34)
			i += print_variable(&str[i + 1], data);
		else if ((str[i] == 39 || str[i] == 34) && quote == 0)
			quote = str[i];
		else if (str[i] != quote)
			ft_putchar_fd(str[i], 1);
		i++;
	}
	return (0);
}
