/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochemsi <ochemsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 01:23:55 by ochemsi           #+#    #+#             */
/*   Updated: 2024/10/14 00:55:49 by ochemsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_availabilty(char *str)
{
	int	i;
	int	flag;

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

int	heredoc(t_file_red *file_red)
{
	char	*tmp;
	int		fd;
	int		flag;
	char	*tmp2;

	tmp = ft_strjoin("/tmp/", file_red->filename);
	fd = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		tmp = readline("> ");
		flag = quotes_availabilty(tmp);
		tmp2 = removed_quotes(file_red->filename);
		if (!ft_memcmp(tmp, tmp2, ft_strlen(file_red->filename)))
			break ;
		write(fd, tmp, ft_strlen(tmp));
		write(fd, "\n", 1);
	}
	close(fd);
	fd = open(tmp, O_RDONLY);
	free(tmp);
	return (fd);
}
