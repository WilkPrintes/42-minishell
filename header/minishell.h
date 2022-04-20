#ifndef MINISHEL_H
# define MINISHEL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"

char	*find_path(char *cmd);
void	command(char *envp, char *ptr);
void	free_matriz(char ***buffer);
void	error(void);

#endif