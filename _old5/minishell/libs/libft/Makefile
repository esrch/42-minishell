NAME = libft.a
LIBFT_SRCS = $(addprefix libft_base/, ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strcmp.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
	ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_free_2d.c ft_free_2d_count.c ft_lstnew.c ft_lstadd_front.c \
	ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
	ft_lstiter.c ft_lstmap.c ft_lstnew_back.c ft_lst_to_arr.c ft_abs.c \
	ft_min.c ft_max.c)
FT_PRINTF_SRCS = $(addprefix ft_printf/, ft_printf.c utils.c parse/parse.c \
	print_utils/print_utils.c print_utils/print_utils_digits.c \
	print_utils/print_utils_padding.c print_utils/print_utils_prefix.c \
	print/print.c print/print_cs.c print/print_duxX.c print/print_p.c \
	ft_printf_error.c)
GNL_SRCS = $(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)
OBJS = $(LIBFT_SRCS:.c=.o) $(FT_PRINTF_SRCS:.c=.o) $(GNL_SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
RM = rm

all: $(NAME)

$(NAME): $(OBJS) libft.h
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean:
	$(RM) -f $(OBJS)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
