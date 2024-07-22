/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:16:42 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/22 13:03:37 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// #include "../minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>

void	commandcheck_pipe(char **envp, char *cmd2, char **cmd1);
void	ft_here_dock(int argc, char **argv, int fd[2]);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
// void	ft_first_command(t_parser *parser, t_list **ls_env, int fd[2]);
// void	ft_all_commands(char *cmd, char **envp, int fd[2]);
// void	ft_last_command(char **argv, char **envp, int argc, int fd[2]);
char	*get_next_line(int fd);
void	close_fd(int fd[2]);

typedef struct var
{
	int	i;
	int	fd[2];
	int	input;
}	t_var;

typedef struct d
{
	int		pid;
	char	**cmd1;
	char	*cmd2;
	char	*cmd;
	int		fl;
}			t_d;

#endif
