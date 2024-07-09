/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:09:26 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/09 03:18:14 by amarouf          ###   ########.fr       */
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
	int pid;
	char **envp;

	envp = ft_list_to_str(env);
	cmd = ft_strjoin("/", split[0]);
	pid = fork();
	if (pid == -1)
		(write(1, "Error:Fork!", 11), exit(1));
	path = ft_checkaccess(envp, ft_strjoin("/", split[0]));
	if (pid == 0)
		(commandcheck(envp, cmd), execve(ft_strjoin(path, cmd), split, envp));
	(free(path), wait(&pid));
}

int ft_redirection(t_parser *parser)
{
	int fd = 1;

	if (parser->red->typeofFile == 4)
	{
		fd = open(parser->red->filename, O_CREAT | O_RDWR, 0644);
		dup2(fd, 1);
		// printf("%d\n", fd);
		// close(fd);
	}
	return (fd);
}

// Commands :) .
void ft_command_check(t_parser *parser, t_list **ls_env)
{
	int fd = 1;
	t_parser *prs = parser;

	if (prs->red)
		fd = ft_redirection(prs);
	if (!ft_memcmp(prs->command[0], "pwd", 4))
		ft_pwd_command();
	else if (!ft_memcmp(prs->command[0], "cd", 3))
		ft_cd_command(prs->command, ft_list_to_str(*ls_env));
	else if (!ft_memcmp(prs->command[0], "echo", 5))
		ft_echo_command(prs->command, ft_list_to_str(*ls_env));
	else if (!ft_memcmp(prs->command[0], "env", 4))
		ft_env_command(*ls_env);
	else if (!ft_memcmp(prs->command[0], "unset", 6))
		ft_unset_command(prs->command, ls_env);
	else if (!ft_memcmp(prs->command[0], "export", 7))
		ft_export_command(prs->command, *ls_env);
	else if (!ft_memcmp(prs->command[0], "exit", 5))
		(write(1, "exit!\n", 6), exit(0));
	else
		shell_commands(prs->command, *ls_env);
	dup2(1, fd);
}

// Split the input .
char **ft_line_split(char *line)
{
	char **split;

	split = ft_split(line, ' ');
	return (split);
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
		{
			in_double_quote = !in_double_quote;
		}
		else if (str[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
		}
		i++;
	}

	if (in_double_quote || in_single_quote)
	{
		return 0;
	}
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
			{
				return (0);
			}
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
			// print_tokens(lexer);
			//
			if (check_words(lexer) == 0)
			{
				write(1, "Syntax error: unclosed quote\n", 30);
				free_lexer(&lexer);
				rd_history = readline(prompt);

				continue;
			}
			fill_parser(lexer, &parser);
			// print_parcer(parser);
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
