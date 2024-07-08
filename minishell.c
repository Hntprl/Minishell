/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochemsi <ochemsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:09:26 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/08 13:45:18 by ochemsi          ###   ########.fr       */
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

// Commands :) .
void ft_command_check(char **split, t_list **ls_env)
{
	if (!ft_memcmp(split[0], "pwd", 4))
		ft_pwd_command();
	else if (!ft_memcmp(split[0], "cd", 3))
		ft_cd_command(split);
	else if (!ft_memcmp(split[0], "echo", 5))
		ft_echo_command(split, ft_list_to_str(*ls_env));
	else if (!ft_memcmp(split[0], "env", 4))
		ft_env_command(*ls_env);
	else if (!ft_memcmp(split[0], "unset", 6))
		ft_unset_command(split, ls_env);
	else if (!ft_memcmp(split[0], "export", 7))
		ft_export_command(split, *ls_env);
	else if (!ft_memcmp(split[0], "exit", 5))
		(write(1, "exit!\n", 6), exit(0));
	else if (!ft_memcmp(split[1], "|", 1))
		pipex(3, split, ft_list_to_str(*ls_env));
	else
		shell_commands(split, *ls_env);
}

// Split the input .
char **ft_line_split(char *line)
{
	char **split;

	split = ft_split(line, ' ');
	return (split);
}

// Read from 0 ...
void minishell(t_list *ls_env)
{
	char *rd_hestory;
	char **split;
	char *prompt;

	prompt = BOLD RED "Mini" YELLOW "shell" RED ">" RESET;
	rd_hestory = readline(prompt);
	while (rd_hestory)
	{
		split = ft_line_split(rd_hestory);
		if (split[0] != NULL)
		{
			add_history(rd_hestory);
			ft_command_check(split, &ls_env);
			free_strings(split);
			free(rd_hestory);
		}
		rd_hestory = readline(prompt);
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	ft_lstclear(&ls_env);
	exit(0);
}
////////////////////////////////////////////////////////////////////////////////////////
// int count_cmds(t_lexer **head)
// {
// 	int count;
// 	count = 0;
// 	while (head)
// 	{
// 		if (head->token == PIPE)
// 			break;
// 		if (head->token == WORD && head->prev && head->prev->token != REDIRECTION_APPEND && head->prev->token != REDIRECTION_IN && head->prev->token != REDIRECTION_OUT && head->prev->token != HEREDOC)
// 			count++;
// 		head = head->next;
// 	}
// 	return (count);
// }
// ls -l > file.txt < file2.txt | grep -i "hello" > file.txt
// void parser(t_lexer *head)
// {
// 	t_parser *parser;
// 	int i;
// 	int j;
// 	int count;
// 	t_lexer *tmp;
// 	tmp = head;
// 	i = 0;
// 	j = 0;
// 	// count = pipe number;
// 	while (tmp)
// 	{
// 		if (tmp->token == PIPE)
// 			j++;
// 		tmp = tmp->next;
// 	}
// 	// malloc parser
// 	parser = malloc(sizeof(t_parser) * j);
// 	tmp = head;
// 	// count commands and allocate memory the pip is split the commands
// 	while(head)
// 	{
// 		count = count_cmds(head);
// 		parser->command = malloc(sizeof(char *) * (count + 1));
// 		parser->next = malloc(sizeof(t_parser));
// 		parser = parser->next;
// 		head = head->next;

// 	}
// 	head = tmp;
// 	while (head)
// 	{

// 		while (head && head->token != PIPE)
// 		{
// 			if(head->prev && head->prev->token != REDIRECTION_APPEND
// 				&& head->prev->token != REDIRECTION_IN
// 				&& head->prev->token != REDIRECTION_OUT
// 				&& head->prev->token != HEREDOC
// 				&& head->prev->token != PIPE)
// 				{
// 					parser->command[i] = ft_strdup(head->str);
// 					i++;
// 				}
// 				head = head->next;
// 		}
// 		head = head->next;
// 	}
// 	head = tmp;
// 		while (head)
// 		{
// 			if ((head->prev && head->prev->token != PIPE )
// 			|| head->prev->token == REDIRECTION_APPEND
// 			|| head->prev->token == REDIRECTION_IN
// 			|| head->prev->token == REDIRECTION_OUT
// 			|| head->prev->token == HEREDOC)
// 			{
// 				parser->red = malloc(sizeof(t_file_red));
// 				parser->red->typeofFile = head->token;
// 				parser->red->filename = ft_strdup(head->next->str);
// 				parser->red->next = NULL;
// 				parser = parser->next;
// 			}
// 			head = head->next;
// 		}
// 	head = tmp;
// 	// print parser
// 	while (parser)
// 	{
// 		i = 0;
// 		while (parser->command[i])
// 		{
// 			printf("command[%d] = %s\n", i, parser->command[i]);
// 			i++;
// 		}
// 		while (parser->red)
// 		{
// 			printf("redirection = %d\n", parser->red->typeofFile);
// 			printf("filename = %s\n", parser->red->filename);
// 			parser->red = parser->red->next;
// 		}
// 		parser = parser->next;
// 	}
// }
#include <stdlib.h>
#include <string.h>

// main function
int main(int ac, char **av)
{
	(void)av;
	t_lexer *lexer;
	t_parser *parser;
	lexer = NULL;
	parser = NULL;
	if (ac == 1)
	{
		tokenize_input(&lexer);
		print_tokens(lexer);
		printf("parser\n");
		fill_parser(lexer, &parser);
		print_parcer(parser);
	}
	exit(0);
}
