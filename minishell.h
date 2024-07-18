/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:10:07 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/17 20:48:17 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
// add path to pipex_bonus.h////////////////////////////
# include "pipex/pipex_bonus.h"
// Prompt
# define RED "\033[31m"
# define RESET "\033[0m"
# define YELLOW "\033[33m"
# define GREEN "\033[32m"
# define BOLD "\033[1m"
# define BR "\033[106m"
# define BG "\033[40m"
# define BLACK "\033[30m"

//////////////////////////////////////////////////////////////////////

// Structs
typedef enum e_tokens
{
	WORD,
	PIPE,
	REDIRECTION_APPEND,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	HEREDOC,
}						t_tokens;

typedef struct s_lexer
{
	char				*str;
	t_tokens			token;
	int					i;
	struct s_lexer		*next;
	struct s_lexer		*prev;
}						t_lexer;

typedef struct s_file_red
{
	t_tokens			typeofFile;
	char				*filename;
	struct s_file_red	*next;
}						t_file_red;

typedef struct s_parser
{
	// int size;
	char				**command;
	t_file_red			*red;
	struct s_parser		*next;
}						t_parser;

typedef struct s_list
{
	struct s_list		*next;
	char				*data;
}						t_list;

////////////////////////////////////////////////////////////////////

// Function calls

// Libft
int						ft_memcmp(const void *s1, const void *s2, size_t n);
char					**ft_split(char const *s, char c);
char					*ft_strdup(const char *s1);
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlen(const char *s);
char					*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
void					free_strings(char **strings);
char					*ft_substr(const char *s, unsigned int start,
							size_t len);
char					*ft_strrchr(const char *s, int c);
// Lincked-list
t_list					*ft_lstnew(char *ontent);
char					**ft_list_to_str(t_list *env);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstclear(t_list **lst);
void					ft_lstdelone(t_list *lst);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					del(void *lst);
int						ft_parsersize(t_parser *lst);
// Commands
void					ft_command_check(t_parser *parser, t_list **ls_env);
void					ft_pwd_command(void);
void					ft_cd_command(char **command, char **env);
void					ft_echo_command(char **command, char **env);
void					ft_env_command(t_list *env);
void					ft_export_command(char **split, t_list *env);
void					ft_unset_command(char **split, t_list **env);
// Environment
void					commandcheck(char **envp, char *cmd2);
char					*ft_findpath(char **env);
char					*ft_checkaccess(char **env, char *cmd);
t_list					*fill_envp(char **env);
char					*ft_find_env_value(char *var_name, char **env);
// Shell-build
void					shell_commands(char **split, t_list *env);
void					minishell(t_list *ls_env);
void					pipex(int argc, char **argv, char **envp);
/////////////////////////////

////////////////////////////

// here_doc.c
int						ft_strncmp(const char *s1, const char *s2, size_t n);
// libft_funcs.c
int						ft_atoi(char *str);

// lexer.c
void					add_token_to_collection(t_lexer **head,t_lexer *new_token);
t_lexer					*create_lexer_token(char *str, t_tokens token);
void					 tokenize_input(t_lexer **head, char *rd_history);
void					print_tokens(t_lexer *head);
// helper.c
void					check_qoutes(char *str);
int						ft_getpid(void);
// parser.c
// void fill_parser(t_lexer *lexer, t_parser **parser)
void					fill_parser(t_lexer *lexer, t_parser **parser);
void					add_command(t_parser **parser, char *cmd, int command_count);
void					add_file_red(t_parser **parser, t_tokens type, char *filename);
void					print_parcer(t_parser *parser);
int						count_commands(t_lexer *head);
t_parser				*create_parser_node(void);
t_file_red				*create_file_red_node(t_tokens type, char *filename);

//free
void	free_parser(t_parser **parser);
void	free_lexer(t_lexer **lexer);

#endif
