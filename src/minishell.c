#include "minishell.h"

int    main(void)
{
    char *ptr;
    char teste[256];
    int pid;
    char *cd;
    char *temp;

    cd = ft_strdup("minishell:~$ ");
    while (1)
    {
        ptr = readline(cd); // scanf diferenciado
        add_history(ptr);
        if (ft_strncmp(ptr, "exit", 4) == 0)
            break ;
        if (ft_strncmp(ptr, "pwd", 3) == 0)
        {    
            getcwd(teste, sizeof(teste)); // Pega atual diretório e coloca no buffer
            printf("%s\n", teste);
        }
        else if (ft_strncmp(ptr, "cds", 3) == 0)
        { 
            chdir(ptr + 4);
            free(cd);
            temp = ft_strjoin("minishell:~/", ptr + 4);
            cd = ft_strjoin(temp, "$ ");
            free(temp);
        }
        else
        {
            pid = fork();
            if (pid == 0)
                command(getenv("PATH"), ptr);
            else
                waitpid(pid, NULL, 0);
        }
        free(ptr);
    }
}