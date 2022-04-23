#include "minishell.h"

void set_dir(char **cd, char *pwd);
void remove_dir(char **pwd);

int    main(void)
{
    char *ptr;
    char teste[256];
    int pid;
    char *cd;
    char *temp;

    getcwd(teste, sizeof(teste)); // Pega atual diretório e coloca no buffer
    cd = ft_strdup("");
    set_dir(&cd, teste);
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
        else if (ft_strncmp(ptr, "cd", 2) == 0)
        {
            chdir(ptr + 3);
            getcwd(teste, sizeof(teste)); // Pega atual diretório e coloca no buffer
            set_dir(&cd, teste);
        }
        else if(ft_strncmp(ptr, "clear", 5) == 0)
            printf("\e[1;1H\e[2J");
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

void set_dir(char **cd, char *pwd)
{
    char *minishell;
    char *temp;
    char *color;

    minishell = ft_strdup("\033[1;32mminishell\e[0m:\033[0;36m");
    if (ft_strncmp(pwd, "/home/", 6) == 0)
        remove_dir(&pwd);
    free(cd[0]);
    color = ft_strjoin(pwd, "\e[0m");
    temp = ft_strjoin(minishell, color);
    cd[0] = ft_strjoin(temp, "$ ");
    free(temp);
    free(color);
}

void remove_dir(char **pwd)
{
    int i;
    int len;
    int count;
    char *temp;
    char *result;

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