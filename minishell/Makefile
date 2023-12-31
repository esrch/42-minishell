NAME = minishell

SRC_FOLDER = src/
SRC_FILES = \
	main.c \
	$(addprefix token/, token.c token_utils.c) \
	$(addprefix token_list/, token_list.c) \
	wildcard_match.c \
	char_tokenizer.c char_tokenizer2.c char_tokenizer3.c \
	filename_expansion.c \
	param_expander.c \
	tokenizer.c tokenizer_word.c tokenizer_utils.c \
	word_split.c
SRCS = $(addprefix $(SRC_FOLDER, $(SRC_FILES)))
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Llibft
LDLIBS = -lreadline -lhistory -lft
SANITIZE_FLAGS = -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean:
	$(MAKE) -C libft fclean
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all

sanitize: CFLAGS += $(SANITIZE_FLAGS)
sanitize: fclean $(NAME)

.PHONY: all clean fclean re sanitize