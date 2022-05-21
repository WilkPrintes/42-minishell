#include "minishell.h"
#include <signal.h>

void set_dir(char **cd, char *pwd);
void remove_dir(char **pwd);

t_test	ito;

void func_doida(char **inate)
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

	sa.sa_handler = handi;
	getcwd(teste, sizeof(teste)); // Pega atual diretório e coloca no buffer
	inate = built_in_functions(); //NOVO
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		func_doida(inate);
	}
}
