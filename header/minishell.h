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
#include <signal.h>

typedef struct s_main {
	char	**cmds;
}				t_main;

typedef struct s_data_var{
	char	**names;
	char	**contents;
	int		count_var;
	int		i_status;
}				t_data_var;

typedef struct s_data
{
	pid_t		pid1;
	int			fd[2];
	char		**cmd;
	char		*path;
}t_data;

char	*find_path(char *cmd);
void	command(char *envp, char *ptr);
void	free_matriz(char ***buffer);
void	error(void);
int		pipex(char *argv[]);

//Mudanças Wilk
void var_func(char *ptr, t_data_var *data);
int find_caracter(char *ptr, char caracter);
void echo (char *ptr, t_data_var *data);
void unset(char *ptr, t_data_var *data);
int var_exists(t_data_var *data, char *name);
int find_content(t_data_var *data, char *ptr, int i);
int		equalexist(char *ptr);

//Mudanças lucas
char	**built_in_functions(void);
int		is_built_in(char **fts, char *str);
void	close_shell(char *ptr);
int		exec_built_in(char *ptr);
void	set_dir(char **cd, char *pwd);
int		parse(char *ptr, t_main *bingo);
void	redirect(char **pars);
void	free_this(char **str);

#endif
