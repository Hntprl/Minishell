/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:10:07 by amarouf           #+#    #+#             */
/*   Updated: 2024/06/01 02:48:28 by amarouf          ###   ########.fr       */
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
// Lincked-list
t_list	*ft_lstnew(char	*ontent);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear_size(t_list **lst, void (*del)(void *), int size);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	del(void *lst);
// Commands
void	ft_command_check(char **split, t_list *ls_env);
void	ft_pwd_command();
void	ft_cd_command(char **split);
void	ft_echo_command(char **split);
void	ft_env_command(t_list *env);
void	ft_export_command(char **split, t_list *env);
void	ft_unset_command(char **split, t_list *env);
// Environment
void	commandcheck(char **envp, char *cmd2);
char	*ft_findpath(char **env);
char	*ft_checkaccess(char **env, char *cmd);
t_list	*fill_envp(char **env);
// Shell-build
void	shell_commands(char **split, t_list *env);
char	**ft_line_split(char *line);
void	minishell(t_list *ls_env);
#endif