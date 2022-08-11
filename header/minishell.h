/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:21:50 by wprintes          #+#    #+#             */
/*   Updated: 2022/07/01 16:21:50 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include "libft.h"

typedef struct s_resources {
	char	**cmds;
	char	**built_in;
	char	*line;
}				t_resources;

typedef struct s_data_var{
	char	**names;
	char	**contents;
	int		count_var;
	int		i_status;
	int		*global;
	int		pipes;
	int		dif_fd[2];
	int		here_doc;
	int		exit;
}				t_data_var;

typedef struct s_data
{
	pid_t		pid1;
	int			fd[2];
	char		**cmd;
	char		*path;
	int			temp_fd;
}t_data;

char	*find_path(char *cmd, char *envp);
void	command(char *envp, char *ptr, t_data_var *data, t_resources *re);
void	free_matriz(char ***buffer);
void	error(void);
int		pipex(char *argv[], t_data_var *data, t_resources *re);
int		var_func(char *ptr, t_data_var *data);
int		find_caracter(char *ptr, char caracter);
void	echo(char **echo, t_data_var *data);
void	unset(char *ptr, t_data_var *data);
int		var_exists(t_data_var *data, char *name);
int		find_content(t_data_var *data, char *ptr, int i);
int		equalexist(char *ptr);
int		find_index(t_data_var *data, char *ptr);
void	env(t_data_var *data);
void	ft_export(t_data_var *data, char **name);
void	set_dir(char **cd, char *pwd);
void	remove_dir(char **pwd);
int		init_vars(t_data_var *data, char *envp[]);
char	**built_in_functions(void);
int		is_built_in(t_resources *resources, char **cmds);
void	close_shell(char **extra, char **cmds, char *ptr, t_data_var *data);
int		exec_built_in(char **cmds, char *ptr, t_data_var *data);
void	set_dir(char **cd, char *pwd);
char	**parse(char *ptr);
void	redirect(char *ptr, t_data_var *data);
int		free_this(char **str);
void	init_args(t_data_var *data, char *envp[]);

char	*remove_quotes(char *ptr);
int		ft_isargument(int c);
int		move_to_cmd(char *ptr, int cmd_nb);
int		number_of_commands(char *ptr);
int		have_quotes(char *ptr);
void	fix_quotes(char *ptr);
void	refix_quotes(char *ptr);
void	remake_quoted(char **ptr);
char	*call_rl(t_data_var *data);
int		single_command(t_resources *resources, t_data_var *data);
int		multiple_commands(t_data_var *data, t_resources *re, int pipes);
void	reset_original_fd(int *original_fd, int *dif_fd);
void	set_original_fd(int *original_fd);
void	handle_sigint(int signum);
void	free_error(char ***ptr, char **path);
int		print_echo(char *str, t_data_var *data);
int		biggest(char *s1, char *s2);
void	exit_clean(char **extra, char **cmds, char *ptr, t_data_var *data);
long	exit_erros(char **extra, char **cmds, char *ptr, t_data_var *data);
int		cd(char **hold, t_data_var *data);

#endif
