/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:43:58 by amarouf           #+#    #+#             */
/*   Updated: 2024/06/25 17:27:40 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*k;
	char	ch;

	ch = c;
	i = 0;
	k = (char *)str;
	while (k[i] != '\0')
	{
		if (k[i] == ch)
			return (k + i);
		i++;
	}
	if (ch == '\0')
		return (k + i);
	return (NULL);
}

char	*ft_editbackup(char *line)
{
	size_t	i;
	char	*backup;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i])
		i ++;
	backup = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!backup)
		return (free(backup), free(line), NULL);
	if (line[i])
		line[i + 1] = '\0';
	return (backup);
}

char	*ft_readline(int fd, char *backup, char *rd)
{
	ssize_t	len;
	char	*tmp;

	while (!ft_strchr(rd, '\n'))
	{
		len = read(fd, rd, BUFFER_SIZE);
		if (len <= 0)
			break ;
		rd[len] = '\0';
		if (backup)
		{
			tmp = backup;
			backup = ft_strjoin(backup, rd);
			free(tmp);
		}
		else
			backup = ft_strdup(rd);
	}
	free(rd);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*rd;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (free(backup), backup = NULL);
	rd = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!rd)
		return (free(backup), backup = NULL);
	rd[0] = '\0';
	line = ft_readline(fd, backup, rd);
	if (!line)
		return (NULL);
	backup = ft_editbackup(line);
	if (!line[0])
		return (free(backup), free(line), backup = NULL);
	return (line);
}
