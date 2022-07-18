/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:58:24 by lucferna          #+#    #+#             */
/*   Updated: 2022/07/18 22:21:32 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

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

	file = open(".temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (file < 0)
		write(2, "Error with delimiter\n", 21);
	while (1)
	{
		buffer = readline("> ");
		ft_putstr_fd(buffer, file);
		ft_putstr_fd("\n", file);
		if (ft_strncmp(limit, buffer, ft_strlen(limit)) == 0)
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
			data->dif_fd[0] = delimiter(ptr[i + 1]);
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
