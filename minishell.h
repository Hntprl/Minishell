/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:10:07 by amarouf           #+#    #+#             */
/*   Updated: 2024/06/26 14:00:48 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>

// Prompt
# define RED "\033[31m"
# define RESET "\033[0m"
# define YELLOW "\033[33m"
# define GREEN "\033[32m"
# define BOLD "\033[1m"
# define BR "\033[106m"
# define BG "\033[40m"
# define BLACK "\033[30m"

typedef struct s_list
{
	struct s_list	*next;
	char			*data;
}	t_list;

// Libft
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	free_strings(char **strings);
char	*ft_substr(const char *s, unsigned int start, size_t len);
// Lincked-list
t_list	*ft_lstnew(char	*ontent);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
void	ft_lstdelone(t_list *lst);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	del(void *lst);
// Commands
void	ft_command_check(char **split, t_list **ls_env);
void	ft_pwd_command(void);
void	ft_cd_command(char **split);
void	ft_echo_command(char **split);
void	ft_env_command(t_list *env);
void	ft_export_command(char **split, t_list *env);
void	ft_unset_command(char **split, t_list **env);
// Environment
void	commandcheck(char **envp, char *cmd2);
char	*ft_findpath(char **env);
char	*ft_checkaccess(char **env, char *cmd);
t_list	*fill_envp(char **env);
// Shell-build
void	shell_commands(char **split, t_list *env);
char	**ft_line_split(char *line);
void	minishell(t_list *ls_env);
// void	pipex(int argc, char **argv, char **envp);
#endif