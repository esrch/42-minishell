NAME = minishell
SRCS = $(addprefix src/, \
	main.c \
	$(addprefix ast/, ast_node.c ast_print.c) \
	$(addprefix char_scanner/, char_scanner.c) \
	$(addprefix env/, env.c) \
	$(addprefix exec/, exec.c) \
	$(addprefix ft_error/, ft_error.c) \
	$(addprefix ft_sprintf_malloc/, ft_sprintf_malloc.c) \
	$(addprefix heredoc/, heredoc.c) \
	$(addprefix parser/, parser.c) \
	$(addprefix redirection_list/, redirection_list.c) \
	$(addprefix tl_scanner/, tl_scanner.c) \
	$(addprefix token/, token.c) \
	$(addprefix token_list/, token_list.c) \
	$(addprefix tokenizer/, tokenizer.c) \
	$(addprefix word_list/, word_list.c) \
)
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc -Ilibft
LDFLAGS = -Llibft
LDLIBS = -lft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

$(LIBFT):
	$(MAKE) -C libft all

clean:
	$(RM) $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all