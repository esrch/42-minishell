# Options
ifeq ($(valgrind), 1)
VALGRIND_PREFIX := valgrind -- 
endif

NO_CLEAN = 0

SRCS_BASE = ../minishell/src
MAIN = $(shell find $(SRCS_BASE) -name main.c)
SRCS = $(filter-out $(MAIN), $(shell find $(SRCS_BASE) -name *.c))
OBJS = $(SRCS:.c=.o)

# TEST_UTILS_SRCS = $(wildcard test_utils/*.c)
# TEST_UTILS_OBJS = $(TEST_UTILS_SRCS:.c=.o)

TEST_DIRS = $(shell find tests -mindepth 1 -maxdepth 1 -type d -printf '%f\n')

CC = cc
CFLAGS = -Wall -Wextra -Werror -I../minishell/includes -Iinc
LDFLAGS = -Llibs
LDLIBS = -lreadline -lhistory -lft -ltest_utils

.PHONY: all clean

all: NO_CLEAN = 1
all: $(TEST_DIRS) clean

.SECONDEXPANSION:
$(TEST_DIRS): %: $$(patsubst .c,.o,$$(wildcard tests/$$*/*.c)) $(OBJS) # $(TEST_UTILS_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $* $(LDLIBS)
	$(VALGRIND_PREFIX) ./$*
	if [ $(NO_CLEAN) = 0 ]; then \
		$(RM) $(OBJS); \
		$(RM) $(TEST_UTILS_OBJS); \
	fi
	$(RM) $*

clean:
	$(RM) $(OBJS)
	# $(RM) $(TEST_UTILS_OBJS)

.SILENT: