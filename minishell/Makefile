NAME = minishell

TOKEN_SRCS = $(addprefix token/, token.c token_list.c)
LEXER_SRCS = $(addprefix lexer/, lexer.c lexer_word.c lexer_utils.c lexer_utils2.c)
OTHER_SRCS = main.c
SRCS = $(TOKEN_SRCS) $(LEXER_SRCS) $(OTHER_SRCS)

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror 
LIBFLAGS = -lreadline -lhistory
SANITIZE_FLAGS = -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

sanitize: fclean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFLAGS) $(SANITIZE_FLAGS) 

.PHONY: all clean fclean re sanitize