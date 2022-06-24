/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:15:27 by wprintes          #+#    #+#             */
/*   Updated: 2022/05/28 16:15:27 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	set_dir(char **cd, char *pwd);
void	remove_dir(char **pwd);
int		equalexist(char *ptr);
void 	emove_dir(char **pwd);
int		find_pipes(char *ptr);

t_main	ito;

void	func_doida(char **inate, t_data_var *data)
{
	char	*ptr;
	int		pid;
	char	*dir;
	char	pwd[256];

	getcwd(pwd, sizeof(pwd));
	set_dir(&dir, pwd);
	ptr = readline(dir); // scanf diferenciado
	if (ptr == NULL)
		close_shell(ptr);
	add_history(ptr);
	parse(ptr, &ito);
	if (find_pipes(ptr) == 1)
	{
		pid = fork();
		if (pid == 0)
			pipex(ito.cmds);
		else
			waitpid(pid, NULL, 0);
	}
	else if (is_built_in(inate, ptr) == 1) //NOVO
		exec_built_in(ptr);
	else if (ft_strncmp(ptr, "clear", 5) == 0)
		printf("\e[1;1H\e[2J");
	else if (equalexist(ptr) != -1)
		var_func(ptr, data);
	else if (ft_strncmp(ptr, "echo", 4) == 0)
		echo(ptr, data);
	else if (ft_strncmp(ptr, "unset", 5) == 0)
		unset(ptr, data);
	else if (*ptr)
	{
		pid = fork();
		if (pid == 0)
			command(getenv("PATH"), ptr);
		else
			waitpid(pid, NULL, 0);
	}
	free_this(ito.cmds);
	free_this(ito.resto);
	free(ptr);
}

int find_pipes(char *ptr)
{
	int len;

	len = 0;

	while(ptr[len] != '\0')
	{
		if (ptr[len] == '|')
			return (1);
		len++;
	}
	return (0);
}

int	equalexist(char *ptr)
{
	if (find_caracter(ptr, ' ') != -1)
		return (-1);
	return (find_caracter(ptr, '='));
}

int	find_caracter(char *ptr, char caracter) // procura um caractere em uma string e retorna a posiçaõ dela (-1 para caso não ache)
{
	int	ptr_len;
	int	i;

	ptr_len = ft_strlen(ptr);
	i = 0;
	while (i < ptr_len)
	{
		if (ptr[i] == caracter)
			return (i);
		i++;
	}
	return (-1);
}

void	handi(int signum)
{
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

int	main(void)
{
	char				**inate;
	struct sigaction	sa;
	t_data_var			data;

	sa.sa_handler = handi;
	inate = built_in_functions();
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	data.count_var = 0;
	data.names = malloc(sizeof(char *) * 1024); //temporário, só pra dizer que funciona :D
	data.contents = malloc(sizeof(char *) * 1024);
	while (1)
		func_doida(inate, &data);
}

void	set_dir(char **cd, char *pwd)
{
	char *minishell;
	char *temp;
	char *color;

	minishell = ft_strdup("\033[1;32mminishell@42\e[0m:\033[0;36m");
	if (ft_strncmp(pwd, "/home/", 6) == 0)
		remove_dir(&pwd);
	free(cd[0]);
	color = ft_strjoin(pwd, "\e[0m");
	temp = ft_strjoin(minishell, color);
	cd[0] = ft_strjoin(temp, "$ ");
	free(temp);
	free(color);
}

void	remove_dir(char **pwd)
{
	int		i;
	int		len;
	int		count;
	char	*temp;
	char	*result;

	temp = getenv("PWD");
	i = 0;
	count = 0;
	len = ft_strlen(temp);
	while(i < len - 1)
	{
		if (temp[i] == '/')
			count++;
		if (count == 3)
			break ;
		i++;
	}
	result = ft_substr(pwd[0], i, ft_strlen(pwd[0]));
	pwd[0] = ft_strjoin("~", result);
}
