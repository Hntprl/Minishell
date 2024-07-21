
NAME = minishell
CFLAGS = -Wall -Wextra -Werror 
RM = rm -rf
CC = cc

SRC = commands.c environment.c lincked_list.c env_commands.c \
	libft_funcs.c free.c lincked_list_clear.c minishell.c split.c \
	commands/cd_command.c commands/echo_command.c \
	parser.c lexer.c helper.c pipe.c \

OSRC = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC)
		$(CC) $(CFLAGS) $(OSRC) -lreadline -o $(NAME) -fsanitize=address 

clean:
	$(RM) $(OSRC)

fclean: clean
		$(RM) $(NAME)
re: fclean all
