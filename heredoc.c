/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochemsi <ochemsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:23:55 by ochemsi           #+#    #+#             */
/*   Updated: 2024/08/07 04:05:51 by ochemsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int heredoc(t_file_red *file_red)
{
    char *tmp;
    int fd;
    int flag;
    char *tmp2;

    tmp = ft_strjoin("/tmp/", file_red->filename);
    fd = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
    while (1)
    {
        tmp = readline("> ");
        flag = quotes_availabilty(tmp);
        tmp2 = removed_quotes(file_red->filename);
        if (!ft_memcmp(tmp, tmp2, ft_strlen(file_red->filename)))
            break;
        // expand
        write(fd, tmp, ft_strlen(tmp));
        write(fd, "\n", 1);
    }
    close(fd);
    fd = open(tmp, O_RDONLY);
    free(tmp);
    return (fd);
}
int quotes_availabilty(char *str)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while (str[i])
    {
        if (str[i] == '\"' || str[i] == '\'')
            flag = 1;
        i++;
    }
    return (flag);
}
char *removed_quotes(char *str)
{
    int i;
    int     j;
    char *tmp;
    int temp;

    i = 0;
    j = 0;
    tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
    while (str[i])
    {
        if (str[i] == '\"' || str[i] == '\'')
        {
            temp = str[i++];
            while (str[i] && str[i] != temp)
                tmp[j++] = str[i++];
            if (str[i] == temp)
                i++;
        }
        else
            tmp[j++] = str[i++];
    }
    tmp[j] = '\0';
    return (tmp);
}
