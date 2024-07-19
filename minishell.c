/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:09:26 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/18 22:48:16 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Array to lincked list .
char **ft_list_to_str(t_list *env)
{
	int i;
	char **envp;

	i = 0;
	envp = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (env)
	{
		envp[i] = env->data;
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

// Execute shell commands (ls , grep ....) .
void shell_commands(char **split, t_list *env)
{
	char *path;
	char *cmd;
	char *joined_cmd;
	int pid;
	char **envp;

	envp = ft_list_to_str(env);
	cmd = ft_strjoin("/", split[0]);
	pid = fork();
	if (pid == -1)
		(write(1, "Error:Fork!", 11), exit(1));
	if (pid == 0)
	{
		joined_cmd = ft_strjoin("/", split[0]);
		path = ft_checkaccess(envp, joined_cmd);
		free(joined_cmd);
		joined_cmd = ft_strjoin(path, cmd);
		(commandcheck(envp, cmd), free(cmd), execve(joined_cmd, split, envp));
	}
	(wait(&pid), free(cmd), free(envp));
}

void ft_redirection(t_file_red *red, int fd)
{
	if (red->typeofFile == REDIRECTION_OUT || red->typeofFile == REDIRECTION_APPEND)
	{
		dup2(fd, 1);
		close(fd);
	}
	else if (red->typeofFile == REDIRECTION_IN)
	{
		dup2(fd, 0);
		close(fd);
	}
}

int ft_buildins(t_parser *parser, t_list **ls_env)
{
	if (!ft_memcmp(parser->command[0], "pwd", 4))
		return (ft_pwd_command(), 1);
	else if (!ft_memcmp(parser->command[0], "cd", 3))
		return (ft_cd_command(parser->command, ft_list_to_str(*ls_env)) ,1);
	else if (!ft_memcmp(parser->command[0], "echo", 5))
		return (ft_echo_command(parser->command, ft_list_to_str(*ls_env)) ,1);
	else if (!ft_memcmp(parser->command[0], "env", 4))
		return (ft_env_command(*ls_env) ,1);
	else if (!ft_memcmp(parser->command[0], "unset", 6))
		return (ft_unset_command(parser->command, ls_env) ,1);
	else if (!ft_memcmp(parser->command[0], "export", 7))
		return (ft_export_command(parser->command, *ls_env) ,1);
	else if (!ft_memcmp(parser->command[0], "exit", 5))
		return ((write(1, "exit\n", 5), exit(0)) ,1);
	else
		return (0);
}

int open_files(t_parser *parser)
{
	int fd;

	fd = 0;
		while (parser->red->next && parser->red->typeofFile == parser->red->next->typeofFile)
			{
				if (parser->red->typeofFile == REDIRECTION_IN)
				{
					if (access(parser->red->filename, F_OK))
					{
						printf("%s: No such file or directory\n", parser->red->filename);
						return (-1337);
					}
				}
				fd = open(parser->red->filename, O_CREAT | O_RDWR, 0644);
				close(fd);
				parser->red = parser->red->next;
			}
		if (parser->red->typeofFile == REDIRECTION_APPEND)
			fd = open(parser->red->filename,  O_RDWR | O_CREAT | O_APPEND, 0644);
		else if (parser->red->typeofFile == REDIRECTION_IN)
		{
			if (access(parser->red->filename, F_OK))
			{
				printf("%s: No such file or directory\n", parser->red->filename);
				return (-1337);
			}
			fd = open(parser->red->filename, O_RDWR, 0644);
		}
		else
			fd = open(parser->red->filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	return (fd);
}

void ft_single_command(t_parser *parser, t_list **ls_env)
{
	int fd = 1;
	int std_in = 0;
	int std_out = 1;
	std_in = dup(0);
	std_out = dup(1);
	
	if (parser->red)
	{
		fd = open_files(parser);
		if (fd == -1337)
			return;
		ft_redirection(parser->red, fd);
	}
	if (ft_buildins(parser, ls_env))
	{
		(dup2(std_out, 1), close(std_out));
		(dup2(std_in, 0), close(std_in));	
		return;
	}
	else
		shell_commands(parser->command, (*ls_env));
	(dup2(std_out, 1), close(std_out));
	(dup2(std_in, 0), close(std_in));
}

// Commands :) .
void ft_command_check(t_parser *parser, t_list **ls_env)
{
	
	if (ft_parsersize(parser) == 1)
		ft_single_command(parser, ls_env);
}

// Read from 0 ...
int check_quotes(const char *str)
{
	bool in_double_quote = false;
	bool in_single_quote = false;
	int i = 0;

	while (str[i])
	{
		if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		i++;
	}
	if (in_double_quote || in_single_quote)
		return 0;
	return 1;
}

int check_words(t_lexer *lexer)
{
	t_lexer *current;

	current = lexer;
	while (current)
	{
		if (current->token == WORD)
		{
			if (check_quotes(current->str) == 0)
				return (0);
		}
		current = current->next;
	}
	return (1);
}
// Read from 0 ...
void minishell(t_list *ls_env)
{
	t_lexer *lexer;
	t_parser *parser;
	char *rd_history;
	char *prompt;

	lexer = NULL;
	parser = NULL;
	prompt = BOLD RED "Mini" YELLOW "shell" RED ">" RESET;
	rd_history = readline(prompt);
	while (rd_history)
	{
		if (rd_history[0])
		{
			add_history(rd_history);
			tokenize_input(&lexer, rd_history);
			if (check_words(lexer) == 0)
			{
				write(1, "Syntax error: unclosed quote\n", 30);
				free_lexer(&lexer);
				rd_history = readline(prompt);
				continue;
			}
			fill_parser(lexer, &parser);
			ft_command_check(parser, &ls_env);
			free_lexer(&lexer);
			free_parser(&parser);
		}
		rd_history = readline(prompt);
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	ft_lstclear(&ls_env);
	exit(0);
}

////////////////////////////////////////////////////////////////////////////////////////

// main function
int main(int ac, char **av, char **env)
{
	(void)av;
	if (ac == 1)
	{
		minishell(fill_envp(env));
	}
	exit(0);
}
