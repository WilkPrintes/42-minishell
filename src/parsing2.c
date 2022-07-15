/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:58:24 by lucferna          #+#    #+#             */
/*   Updated: 2022/07/15 14:07:31 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	have_quotes(char *ptr)
{
	int	i;
	int	val;
	int	quotes;

	i = 0;
	val = 0;
	quotes = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == 34 || ptr[i] == 39)
		{
			val++;
			quotes = ptr[i++];
			while (ptr[i] != '\0' && ptr[i] != quotes)
				i++;
			if (ptr[i] == quotes)
				val++;
		}
		i++;
	}
	if (val % 2 != 0)
		return (-1);
	else if (val == 0)
		return (0);
	return (1);
}

static int	open_close(int old_fd, char *name, int method)
{
	close(old_fd);
	if (method == 1)
		return (open(name, O_RDONLY, 0777));
	else if (method == 2)
		return (open(name, O_RDWR | O_CREAT | O_TRUNC, 0777));
	else
		return (open(name, O_RDWR | O_CREAT | O_APPEND, 0777));
}
static int	delimiter(char *limit)
{
	int		file;
	char	*buffer;

	file = open(".temp_file", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (file < 0)
		write(2, "Error with delimiter\n", 21);
	while (1)
	{
		write(2, "> ", 2);
		buffer = get_next_line(0);
		ft_putstr_fd(buffer, file);
		if (ft_strncmp(limit, buffer, ft_strlen(buffer) - 1) == 0)
			break ;
		free(buffer);
	}
	free(buffer);
	return (file);
}

static void	redirections(char **ptr, t_data_var *data)
{
	int		i;
	int		len;

	i = 0;
	data->dif_fd[0] = dup(STDIN_FILENO);
	data->dif_fd[1] = dup(STDOUT_FILENO);
	while (ptr[i] != NULL)
	{
		len = ft_strlen(ptr[i]);
		if (ft_strncmp(ptr[i], "<", len) == 0 && ptr[i + 1] != NULL)
			data->dif_fd[0] = open_close(data->dif_fd[0], ptr[i + 1], 1);
		else if (ft_strncmp(ptr[i], "<<", len) == 0 && ptr[i + 1] != NULL)
			data->here_doc = delimiter(ptr[i + 1]);
		else if (ft_strncmp(ptr[i], ">", len) == 0 && ptr[i + 1] != NULL)
			data->dif_fd[1] = open_close(data->dif_fd[1], ptr[i + 1], 2);
		else if (ft_strncmp(ptr[i], ">>", len) == 0 && ptr[i + 1] != NULL)
			data->dif_fd[1] = open_close(data->dif_fd[1], ptr[i + 1], 3);
		i++;
	}
	dup2(data->dif_fd[0], STDIN_FILENO);
	dup2(data->dif_fd[1], STDOUT_FILENO);
}

void	redirect(char *ptr, t_data_var *data)
{
	int		i;
	char	**hold;

	if (ptr[0] == '\0')
		return ;
	i = 0;
	hold = ft_split(ptr, ' ');
	while (hold[i] != NULL)
	{
		if (have_quotes(hold[i]) == 1)
			hold[i] = remove_quotes(hold[i]);
		refix_quotes(hold[i++]);
	}
	redirections(hold, data);
	free_this(hold);
}
