#include "minishell.h"

int var_exists(t_data_var *data, char *name);
int find_content(t_data_var *data, char *ptr, int i);

void var_func(char *ptr, t_data_var *data)
{
    int p;
    int i;
    int len;
    int exists;
    char *name;
     
    i = data->count_var;
    p = find_caracter(ptr, '=');
    len = ft_strlen(ptr);
    name = ft_substr(ptr, 0, p);
    exists = var_exists(data, name);
    if (i > 0 && exists != -1)
        data->contents[exists] = ft_substr(ptr, p + 1, len);
    else
    {
        data->names[i] = ft_strdup(name);
        data->contents[i] = ft_substr(ptr, p + 1, len);
        data->count_var++;
    }
    printf("%d\n", data->count_var);
    free(name);
}

void echo (char *ptr,  t_data_var *data)
{
    int len;
    int i;

    len = ft_strlen(ptr);
    i = 5;
    while (i < len)
    {
        if (ptr[i] != '$')
            printf("%c", ptr[i]);
        else
            i = find_content(data, ptr, i);
        i++;
    }
    printf("\n");
}

int find_content(t_data_var *data, char *ptr, int i)
{
    char *name;
    int len;
    int exists;

    len = find_caracter(ptr+i, ' ');
    if (len == -1)
        len = ft_strlen(ptr) - i;
    len = len + i;
    name = ft_substr(ptr, i + 1, len);
    exists = var_exists(data, name);
    if (exists != -1)
        printf("%s", data->contents[exists]);
    return (len);
}

int var_exists(t_data_var *data, char *name)
{
    int i;

    i = 0;
    while(i < data->count_var)
    {
        if (ft_strncmp(name, data->names[i], ft_strlen(name)) == 0)
            return (i);
        i++;
    }
    return (-1);
}