/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochemsi <ochemsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:52:00 by ochemsi           #+#    #+#             */
/*   Updated: 2024/07/08 10:52:31 by ochemsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get pid of current process
int ft_getpid(void)
{
    int fd;
    char buffer[256];
    ssize_t bytes_read;
    int pid;
    char *ptr;

    fd = open("/proc/self/stat", O_RDONLY);
    if (fd == -1)
        exit(1);
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1)
    {
        close(fd);
        exit(1);
    }
    buffer[bytes_read] = '\0';
    close(fd);
    ptr = buffer;
    while (*ptr != ' ' && *ptr != '\0')
    {
        ptr++;
    }
    return (pid = ft_atoi(buffer));
}

void check_qoutes(char *str)
{
	int i;
	int qoutes;
	int double_qoutes;

	i = 0;
	qoutes = 0;
	while (str[i])
	{
		if (str[i] == '"')
			double_qoutes++;
		if (str[i] == '\'')
			qoutes++;
		i++;
	}
	if (qoutes % 2 != 0 || double_qoutes % 2 != 0)
	{
		write(1, "Error: qoutes still open!\n", 26);
		exit(1);
	}
}