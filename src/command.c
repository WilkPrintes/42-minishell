/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:15:32 by wprintes          #+#    #+#             */
/*   Updated: 2022/05/28 16:15:32 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo (char *ptr,  t_data_var *data)
{
    int len;
    int i;
    int flag;

    len = ft_strlen(ptr);
    if (ft_strncmp(ptr, "echo -n", 7) == 0)
    {
        flag = 1;
        i = 8;
    }
    else
    {
        flag = 0;
        i = 5;
    }
    while (i < len)
    {
        if (ptr[i] != '$')
            printf("%c", ptr[i]);   
        else
            i = i + find_content(data, ptr, i);
        i++;
    }
    if (flag == 0)
        printf("\n");
}

void unset(char *ptr, t_data_var *data)
{
    int     exists;
    char    *name_temp;
    char    *content_temp;
    
    int     i;
    
    exists = var_exists(data, ptr+6);
    if (exists != -1)
    {
        while (exists < data->count_var - 1)
        {
            name_temp = ft_strdup(data->names[exists + 1]);
            content_temp = ft_strdup(data->contents[exists + 1]);
            data->names[exists] = ft_strdup(name_temp);
            data->contents[exists] = ft_strdup(content_temp);
            free(name_temp);
            free(content_temp);
            exists++;
        }
        data->count_var--;
    }
}
