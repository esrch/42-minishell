NAME = libtest_utils.a
SRCS = test_suite.c assert.c
OBJS = $(SRCS:.c=.o)
AR_OBJS = $(patsubst %, '$(NAME)(%)', $(OBJS))

CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar
ARFLAGS = rcs

RM = rm -f

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $^
	$(RM) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all