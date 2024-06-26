
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
CC = cc

SRC = commands.c environment.c lincked_list.c env_commands.c \
	libft_funcs.c lincked_list_clear.c minishell.c split.c \
	pipex/pipex_bonus.c pipex/pipex_utils_bonus.c \
	pipex/here_doc.c pipex/get_next_line.c pipex/commandcheck.c \

OSRC = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC)
		$(CC) $(CFLAGS) $(OSRC) -lreadline -o $(NAME) -fsanitize=address

clean:
	$(RM) $(OSRC)

fclean: clean
		$(RM) $(NAME)
re: fclean all
