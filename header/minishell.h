#ifndef MINISHEL_H
# define MINISHEL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "libft.h"

typedef struct s_test {
	char	**pars;
}				t_test;

char	*find_path(char *cmd);
void	command(char *envp, char *ptr);
void	free_matriz(char ***buffer);
void	error(void);

//Mudanças lucas
char	**built_in_functions(void);
int	is_built_in(char **fts, char *str);
void close_shell(char *ptr);
int	exec_built_in(char *ptr);
void set_dir(char **cd, char *pwd);

#endif
