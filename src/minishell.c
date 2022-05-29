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

void set_dir(char **cd, char *pwd);
void remove_dir(char **pwd);
int equalexist(char *ptr);

t_main	ito;

void func_doida(char **inate, t_data_var *data)
{
	int		pid;
	
	ito.ptr = readline("minishell: "); // scanf diferenciado
	if (ito.ptr == NULL)
		close_shell(ito.ptr);
	add_history(ito.ptr);
	if (is_built_in(inate, ito.ptr) == 1) //NOVO
		exec_built_in(ito.ptr);
	else if(ft_strncmp(ito.ptr, "clear", 5) == 0)
		printf("\e[1;1H\e[2J");
	else if (equalexist(ito.ptr) != -1)
		var_func(ito.ptr, data);
	else if (ft_strncmp(ito.ptr, "echo", 4) == 0)
		echo(ito.ptr, data);
	else if (ft_strncmp(ito.ptr, "unset", 5) == 0)
		unset(ito.ptr, data);
	else if (*ito.ptr)
	{
		pid = fork();
		if (pid == 0)
			command(getenv("PATH"), ito.ptr);
		else
			waitpid(pid, NULL, 0);
	}
	free(ito.ptr);
}

int equalexist(char *ptr)
{
	if (find_caracter(ptr, ' ') != -1)
		return (-1);
	return (find_caracter(ptr, '='));
}

int find_caracter(char *ptr, char caracter) // procura um caractere em uma string e retorna a posiçaõ dela (-1 para caso não ache)
{
	int ptr_len;
	int i;

	ptr_len = ft_strlen(ptr);
	i = 0;
	while (i < ptr_len)
	{
		if (ptr[i] == caracter)
			return(i);
		i++;
	}
	return (-1);
}

void handi(int signum)
{
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

int	main(void)
{
	char teste[256];
	char **inate; //NOVO
	struct sigaction sa;
	t_data_var data;

	sa.sa_handler = handi;
	getcwd(teste, sizeof(teste)); // Pega atual diretório e coloca no buffer
	inate = built_in_functions(); //NOVO
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	data.count_var = 0;
	data.names = malloc(sizeof(char *) * 1024); //temporário, só pra dizer que funciona :D
	data.contents = malloc(sizeof(char *) * 1024);
	while (1)
		func_doida(inate, &data);
}
