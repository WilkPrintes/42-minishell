/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:06:02 by lucferna          #+#    #+#             */
/*   Updated: 2022/07/22 21:19:58 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_original_fd(int *original_fd)
{
	original_fd[0] = dup(STDIN_FILENO);
	original_fd[1] = dup(STDOUT_FILENO);
}

void	reset_original_fd(int *original_fd, int *dif_fd)
{
	if (dif_fd[0] != STDIN_FILENO)
		close(dif_fd[0]);
	if (dif_fd[1] != STDOUT_FILENO)
		close(dif_fd[1]);
	if (access(".temp_file", F_OK) == 0)
		unlink(".temp_file");
	dup2(original_fd[0], STDIN_FILENO);
	dup2(original_fd[1], STDOUT_FILENO);
}

int	biggest(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	size;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
		size = len1;
	else
		size = len2;
	return (size);
}
