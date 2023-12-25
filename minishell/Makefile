NAME = minishell

TOKEN_SRCS = $(addprefix token/, token.c token_list.c)
CHAR_LEXER_SRCS = $(addprefix char_lexer/, char_lexer.c char_lexer2.c char_lexer3.c)
LEXER_SRCS = $(addprefix lexer/, lexer.c lexer_word.c lexer_utils.c)
OTHER_SRCS = main.c
SRCS = $(TOKEN_SRCS) $(CHAR_LEXER_SRCS) $(LEXER_SRCS) $(OTHER_SRCS)

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -lreadline -lhistory -Llibft -lft
SANITIZE_FLAGS = -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFLAGS)

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean:
	$(MAKE) -C libft fclean
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all

sanitize: fclean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFLAGS) $(SANITIZE_FLAGS) 

.PHONY: all clean fclean re sanitize