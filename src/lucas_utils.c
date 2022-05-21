#include "minishell.h"

char	**built_in_functions(void) //NOVO
{
	char **ptr;

	ptr = malloc(3 * sizeof(char *));
	ptr[0] = ft_strdup("cd");
	ptr[1] = ft_strdup("pwd");
	ptr[2] = ft_strdup("exit");
	return (ptr);
}

int	is_built_in(char **fts, char *str) //NOVO
{
	int	i;

	i = 0;
	while (i < 3)
	{	//Mudar strlen para tamanho certo após parsing
		if (ft_strncmp(fts[i], str, ft_strlen(fts[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

void close_shell(char *ptr) //NOVO
{
	free(ptr);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int	exec_built_in(char *ptr) //NOVO
{
	char teste[256];

	if (ft_strncmp(ptr, "exit", 4) == 0)
			close_shell(ptr);
	else if (ft_strncmp(ptr, "pwd", 3) == 0)
	{
		getcwd(teste, sizeof(teste)); // Pega atual diretório e coloca no buffer
			printf("%s\n", teste);
	}
	else if (ft_strncmp(ptr, "cd", 2) == 0)
	{
		chdir(ptr + 3);
		getcwd(teste, sizeof(teste)); // Pega atual diretório e coloca no buffer
	}
	return (0);
}
