# Sources
MAIN = $(shell find ../minishell/src -type f -name main.c)
APP_SRCS = $(shell find ../minishell/src -type f -name *.c)
LIB_SRCS = $(shell find ../minishell/libs/libft -type f -name *.c)
SRCS = $(filter-out $(MAIN) $(EXCLUDE_SRCS), $(APP_SRCS) $(LIB_SRCS))
# Includes
INC = ../minishell/inc ../minishell/libs/libft

# Files
OBJS = $(SRCS:.c=.o)
TEST_SRCS = $(shell find tests/* -type f -name *.c)
TEST_OBJS = $(TEST_SRCS:.c=.o)
TESTS = $(notdir $(basename $(TEST_SRCS)))

TEST_UTILS_SRCS = $(shell find utils/* -type f -name *.c)
TEST_UTILS_OBJS = $(TEST_UTILS_SRCS:.c=.o);
#Flags
CFLAGS = -Wall -Wextra -Werror -Iinc $(patsubst %, -I%, $(INC))
LDFLAGS = -Llibs
LDLIBS = -lreadline -ltest_utils

# Options
ifeq ($(valgrind), 1)
VALGRIND_PREFIX := valgrind -- 
else ifeq ($(valgrind), 2)
VALGRIND_PREFIX := valgrind --leak-check=full
endif

.PHONY: all

all: $(TESTS)

.SECONDEXPANSION:
$(TESTS): %: $$(patsubst .c, .o, $$(wildcard tests/$$*.c)) $(OBJS) $(TEST_UTILS_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o out/$* $(LDLIBS)
	$(VALGRIND_PREFIX) ./out/$*
	$(RM) ./out/$*

clean:
	$(RM) $(OBJS)
	$(RM) $(TEST_OBJS)
	$(RM) $(TEST_UTILS_OBJS)
	$(RM) $(wildcard ./out/*)

.SILENT: