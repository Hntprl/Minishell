/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:57:39 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/20 18:58:37 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// void	ft_here_dock(int argc, char **argv, int fd[2])
// {
// 	int		pid;
// 	char	*str;

// 	(void)argc;
// 	str = NULL;
// 	pid = fork();
// 	if (pid == -1)
// 		exit(EXIT_FAILURE);
// 	if (pid == 0)
// 	{
// 		while (1)
// 		{
// 			str = get_next_line(0);
// 			if (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0)
// 			{
// 				(free(str), close_fd(fd));
// 				exit(1);
// 			}
// 			write(fd[1], str, ft_strlen(str));
// 			free(str);
// 		}
// 	}
// }
