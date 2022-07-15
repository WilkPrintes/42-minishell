/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:06:02 by lucferna          #+#    #+#             */
/*   Updated: 2022/07/15 21:06:37 by lucferna         ###   ########.fr       */
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
	dup2(original_fd[0], STDIN_FILENO);
	dup2(original_fd[1], STDOUT_FILENO);
}
