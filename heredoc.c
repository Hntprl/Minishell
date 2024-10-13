/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochemsi <ochemsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:23:55 by ochemsi           #+#    #+#             */
/*   Updated: 2024/10/13 16:15:12 by ochemsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *remove_quotes(char *str)
{
    int in_single_quote = 0;
    int in_double_quote = 0;
    char *str2;
    str2 = malloc(sizeof(char) * (strlen(str) + 1));
    int i , j;
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '\'' && in_double_quote == 0)
            in_single_quote = !in_single_quote;
        else if (str[i] == '"' && in_single_quote == 0)
            in_double_quote = !in_double_quote;
        else 
        {
            str2[j] = str[i];
            j++;
        }
        i++;
    }
    return (str2);
}
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
