
NAME = minishell
CFLAGS = -Wall -Wextra -Werror 
RM = rm -rf
CC = cc

SRC = buildins/cd.c buildins/echo.c buildins/export.c \
		standard/libft_funcs.c standard/libft_funcs2.c standard/libft_funcs3.c \
		standard/lincked_list_clear.c standard/lincked_list.c \
		parsing/parsing_helper.c parsing/parser.c parsing/parser_helper.c parsing/parsing.c parsing/lexer.c parsing/lexer_helper.c\
		commands.c env_commands.c environment.c free.c minishell.c \
		heredoc.c pipe.c split.c single_multiple.c redirections.c\

OSRC = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC)
		$(CC) $(CFLAGS) $(OSRC) -lreadline -o $(NAME) -fsanitize=address

clean:
	$(RM) $(OSRC)

fclean: clean
		$(RM) $(NAME)
re: fclean all
