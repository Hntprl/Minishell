
NAME = minishell
CFLAGS = -Wall -Wextra -Werror 
RM = rm -rf
CC = cc

SRC = commands.c environment.c lincked_list.c env_commands.c parser_helper.c lexer_helper.c\
	libft_funcs.c libft_funcs2.c libft_funcs3.c free.c lincked_list_clear.c minishell.c split.c \
	commands/cd.c commands/echo.c parsing.c parsing_helper.c \
	parser.c lexer.c  pipe.c commands/export.c \

OSRC = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC)
		$(CC) $(CFLAGS) $(OSRC) -lreadline -o $(NAME) -fsanitize=address

clean:
	$(RM) $(OSRC)

fclean: clean
		$(RM) $(NAME)
re: fclean all
