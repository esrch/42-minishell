BASE_FOLDER = ../minishell/
ASSERT_OBJS = assert/assert.o
DEPENDENCY_FOLDERS = token char_lexer lexer param_expander
DEPENDENCY_SRCS = $(wildcard $(patsubst %, $(BASE_FOLDER)%/*.c, $(DEPENDENCY_FOLDERS)))
DEPENDENCY_OBJS = $(patsubst %.c, %.o, $(DEPENDENCY_SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L.
LDLIBS = -lreadline -lhistory -lft

valgrind-%: %_test.o $(ASSERT_OBJS) $(DEPENDENCY_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)
	valgrind -- ./$@
	rm -f $@

%: %_test.o $(ASSERT_OBJS) $(DEPENDENCY_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)
	./$@
	rm -f $@

clean:
	rm -f *.o
	rm -f $(ASSERT_OBJS)
	rm -f $(DEPENDENCY_OBJS)

.PHONY: test
.SILENT: